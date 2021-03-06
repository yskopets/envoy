# Python binary that stitches together the various tools.type_whisperer.Types
# protos generated by type_whisperer.py for the entire API. The result is a type
# database in tools.type_whisperer.TypeDb format.

import re
import sys

from google.protobuf import text_format

from tools.api_proto_plugin.utils import BazelBinPathForOutputArtifact
from tools.type_whisperer.api_type_db_pb2 import TypeDb
from tools.type_whisperer.types_pb2 import Types, TypeDescription

# Regexes governing v3alpha upgrades. TODO(htuch): The regex approach will have
# to be rethought as we go beyond v3alpha, this is WiP.
TYPE_UPGRADE_REGEXES = [
    (r'(envoy[\w\.]*\.)(v2alpha\d?|v2)', r'\1v3alpha'),
    # These are special cases, e.g. upgrading versionless packages.
    ('envoy\.type\.matcher', 'envoy.type.matcher.v3alpha'),
    ('envoy\.type', 'envoy.type.v3alpha'),
]

# As with TYPE_UPGRADE_REGEXES but for API .proto paths.
PATH_UPGRADE_REGEXES = [
    (r'(envoy/[\w/]*/)(v2alpha\d?|v2)', r'\1v3alpha'),
    # These are special cases, e.g. upgrading versionless packages.
    ('envoy/type/matcher', 'envoy/type/matcher/v3alpha'),
    ('envoy/type', 'envoy/type/v3alpha'),
]

# These packages must be upgraded to v3alpha, even if there are no protos
# modified. This is largely for situations where we know we want to be doing
# structural change to have the APIs follow the x/y//vN/z.proto structure of
# organization.
PKG_FORCE_UPGRADE = [
    'envoy.api.v2',
    'envoy.api.v2.auth',
    'envoy.api.v2.cluster',
    'envoy.api.v2.core',
    'envoy.api.v2.endpoint',
    'envoy.api.v2.listener',
    'envoy.api.v2.ratelimit',
    'envoy.api.v2.route',
    'envoy.type',
    'envoy.type.matcher',
]


def UpgradedType(type_name):
  """Determine upgraded type name."""
  for pattern, repl in TYPE_UPGRADE_REGEXES:
    s = re.sub(pattern, repl, type_name)
    if s != type_name:
      return s


def UpgradedPath(proto_path):
  """Determine upgraded API .proto path."""
  for pattern, repl in PATH_UPGRADE_REGEXES:
    s = re.sub(pattern, repl, proto_path)
    if s != proto_path:
      return s


def LoadTypes(path):
  """Load a tools.type_whisperer.Types proto from the filesystem.

  Args:
    path: filesystem path for a file in text proto format.

  Returns:
    tools.type_whisperer.Types proto loaded from path.
  """
  types = Types()
  with open(path, 'r') as f:
    text_format.Merge(f.read(), types)
  return types


def NextVersionUpgrade(type_name, type_map, next_version_upgrade_memo, visited=None):
  """Does a given type require upgrade between major version?

  Performs depth-first search through type dependency graph for any upgraded
  types that will force type_name to be upgraded.

  Args:
    type_name: fully qualified type name.
    type_map: map from type name to tools.type_whisperer.TypeDescription.
    next_version_upgrade_memo: a memo dictionary to avoid revisiting nodes across invocations.
    visited: a set of visited nodes in the current search, used to detect loops.

  Returns:
    A boolean indicating whether the type requires upgrade.
  """
  if not visited:
    visited = set([])
  # Ignore non-API types.
  if not type_name.startswith('envoy'):
    return False
  # If we have a loop, we can't learn anything new by circling around again.
  if type_name in visited:
    return False
  visited = visited.union(set([type_name]))
  # If we have seen this type in a previous NextVersionUpgrade(), use that
  # result.
  if type_name in next_version_upgrade_memo:
    return next_version_upgrade_memo[type_name]
  type_desc = type_map[type_name]
  # Force upgrade packages that we enumerate.
  if type_desc.qualified_package in PKG_FORCE_UPGRADE:
    return True
  # Recurse and memoize.
  should_upgrade = type_desc.next_version_upgrade or any(
      NextVersionUpgrade(d, type_map, next_version_upgrade_memo, visited)
      for d in type_desc.type_dependencies)
  next_version_upgrade_memo[type_name] = should_upgrade
  return should_upgrade


if __name__ == '__main__':
  # Root of source tree.
  src_root = sys.argv[1]
  # Output path for type database.
  out_path = sys.argv[2]
  # Bazel labels for source .proto.
  src_labels = sys.argv[3:]

  # Load type descriptors for each .proto.
  type_desc_paths = [
      BazelBinPathForOutputArtifact(label, '.types.pb_text', root=src_root) for label in src_labels
  ]
  type_whispers = map(LoadTypes, type_desc_paths)
  # Aggregate type descriptors to a single type map.
  type_map = dict(sum([list(t.types.items()) for t in type_whispers], []))
  all_pkgs = set([type_desc.qualified_package for type_desc in type_map.values()])

  # Determine via DFS on each type descriptor and its deps which packages require upgrade.
  next_version_upgrade_memo = {}
  next_versions_pkgs = set([
      type_desc.qualified_package
      for type_name, type_desc in type_map.items()
      if NextVersionUpgrade(type_name, type_map, next_version_upgrade_memo)
  ])

  # Generate type map entries for upgraded types.
  upgraded_types = []
  for type_name, type_desc in type_map.items():
    if type_desc.qualified_package in next_versions_pkgs:
      upgrade_type_desc = TypeDescription()
      upgrade_type_desc.qualified_package = UpgradedType(type_desc.qualified_package)
      upgrade_type_desc.proto_path = UpgradedPath(type_desc.proto_path)
      upgraded_types.append((UpgradedType(type_name), upgrade_type_desc))
  for n, t in upgraded_types:
    type_map[n] = t

  # Generate the type database proto. To provide some stability across runs, in
  # terms of the emitted proto binary blob that we track in git, we sort before
  # loading the map entries in the proto. This seems to work in practice, but
  # has no guarantees.
  type_db = TypeDb()
  next_proto_path = {}
  for t in sorted(type_map):
    type_desc = type_db.types[t]
    type_desc.qualified_package = type_map[t].qualified_package
    type_desc.proto_path = type_map[t].proto_path
    if type_desc.qualified_package in next_versions_pkgs:
      type_desc.next_version_type_name = UpgradedType(t)
      assert (type_desc.next_version_type_name != t)
      next_proto_path[type_map[t].proto_path] = type_map[
          type_desc.next_version_type_name].proto_path
  for pkg in sorted(all_pkgs):
    if pkg in next_versions_pkgs:
      type_db.next_version_packages[pkg] = UpgradedType(pkg)
  for proto_path in sorted(next_proto_path):
    type_db.next_version_proto_paths[proto_path] = UpgradedPath(proto_path)

  # Write out proto text.
  with open(out_path, 'w') as f:
    f.write(str(type_db))
