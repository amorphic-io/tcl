#include "tclBazelDefaultPaths.h"

#include <unistd.h>
#include <limits.h>
#include <memory>
#include <string>

#include "rules_cc/cc/runfiles/runfiles.h"

namespace {

using rules_cc::cc::runfiles::Runfiles;

std::string GetExePath() {
  char result[PATH_MAX];
  ssize_t count = readlink("/proc/self/exe", result, PATH_MAX);
  return std::string(result, (count > 0) ? count : 0);
}

std::string Parent(std::string path) {
  std::size_t pos = path.rfind('/');
  if (pos == std::string::npos || pos == 0) {
    fprintf(stderr, "Invalid path: %s\n", path.c_str());
    abort();
  }
  return path.substr(0, pos);
}

std::string FindLibraryDirFromFilePath(std::string target) {
  std::string error;
  auto runfiles =
      std::unique_ptr<Runfiles>(Runfiles::Create(GetExePath(), &error));
  if (runfiles == nullptr) {
    fprintf(stderr, "Failed to create Runfiles object: %s\n", error.c_str());
    abort();
  }
  return runfiles->Rlocation(target);
}

class Paths {
 public:
  Paths(const std::string &runfiles_path, const std::string &library_path)
      : runfiles_path_(runfiles_path), library_path_(library_path) {}

  const char *runfiles_path() const {
    return runfiles_path_.c_str();
  }
  const char *library_path() const {
    return library_path_.c_str();
  }

  const char *RemapPkgConfigValue(const char *key, const char *value) const {
    if (std::string(key) == "scriptdir,runtime") {
      return library_path();
    }
    return value;
  }

 private:
  std::string runfiles_path_;
  std::string library_path_;
};

std::unique_ptr<Paths> paths;

const Paths *GetOrInitPaths() {
  if (paths) {
    return paths.get();
  }
  // Allocate once.
  const std::string path = FindLibraryDirFromFilePath("tcl/library/init.tcl");
  const std::string library_path = Parent(path);
  const std::string runfiles_path = Parent(library_path);
  paths = std::make_unique<Paths>(runfiles_path, library_path);
  return paths.get();
}
} // namespace

const char *getDefaultLibraryDir() {
  return GetOrInitPaths()->library_path();
}

const char *getDefaultPkgPath(void) {
  return GetOrInitPaths()->runfiles_path();
}


const char *remapTclPkgConfig(const char *key, const char *value) {
  return GetOrInitPaths()->RemapPkgConfigValue(key, value);
}
