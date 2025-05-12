#ifndef _TCLDEFAULTLIBRARYDIR
#define _TCLDEFAULTLIBRARYDIR

#ifdef __cplusplus
extern "C" {
#endif
  /*
   * Default directory in which to look for Tcl library scripts. The symbol is
   * defined by Makefile.
   */
  const char *getDefaultLibraryDir(void);

  /*
   * Directory in which to look for packages (each package is typically
   * installed as a subdirectory of this directory). The symbol is defined by
   * Makefile.
   */
  const char *getDefaultPkgPath(void);

  // Remap internal config paths to special locations.
  // Used in generic/tclConfig.c to remap macro paths to internal
  // runfiles paths.
  const char *remapTclPkgConfig(const char *key, const char *value);
#ifdef __cplusplus
}
#endif

#endif  // _TCLDEFAULTLIBRARYDIR
