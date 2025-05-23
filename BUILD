# Copyright 2020 Google LLC
#
# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
#
#      http://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.

""" Tcl scripting language. """

load("@rules_cc//cc:defs.bzl", "cc_binary", "cc_library")

licenses(["notice"])

exports_files(["LICENSE"])

# The following settings are taken from the command line build when executing
# configure :
TCL_BASE_COPTS = [
    "-DHAVE_ZLIB=",  # Enables ZLIB
    "-DTCL_DBGX=",
    "-DHAVE_LIMITS_H=1",
    "-DHAVE_UNISTD_H=1",
    "-DHAVE_SYS_PARAM_H=1",
    "-DUSE_THREAD_ALLOC=1",
    "-D_REENTRANT=1",
    "-D_THREAD_SAFE=1",
    "-DHAVE_PTHREAD_ATTR_SETSTACKSIZE=1",
    "-DHAVE_PTHREAD_ATFORK=1",
    "-DTCL_THREADS=1",
    "-DPEEK_XCLOSEIM=1",
    "-D_LARGEFILE64_SOURCE=1",
    "-DTCL_WIDE_INT_TYPE=long\\ long",
    "-DHAVE_GETCWD=1",
    "-DHAVE_OPENDIR=1",
    "-DHAVE_STRSTR=1",
    "-DHAVE_STRTOL=1",
    "-DHAVE_STRTOLL=1",
    "-DHAVE_STRTOULL=1",
    "-DHAVE_TMPNAM=1",
    "-DHAVE_WAITPID=1",
    "-DHAVE_GETPWUID_R_5=1",
    "-DHAVE_GETPWUID_R=1",
    "-DHAVE_GETPWNAM_R_5=1",
    "-DHAVE_GETPWNAM_R=1",
    "-DHAVE_GETGRGID_R_5=1",
    "-DHAVE_GETGRGID_R=1",
    "-DHAVE_GETGRNAM_R_5=1",
    "-DHAVE_GETGRNAM_R=1",
    "-DUSE_TERMIOS=1",
    "-DTIME_WITH_SYS_TIME=1",
    "-DHAVE_TM_ZONE=1",
    "-DHAVE_GMTIME_R=1",
    "-DHAVE_LOCALTIME_R=1",
    "-DHAVE_TM_GMTOFF=1",
    "-DHAVE_SYS_TIME_H=1",
    "-DHAVE_TIMEZONE_VAR=1",
    "-DHAVE_ST_BLKSIZE=1",
    "-DSTDC_HEADERS=1",
    "-DHAVE_SIGNED_CHAR=1",
    "-DHAVE_LANGINFO=1",
    "-DHAVE_SYS_IOCTL_H=1",
    "-DTCL_SHLIB_EXT=\\\".so\\\"",
    "-Wno-implicit-int",
    "-fno-strict-aliasing",
    "-fPIC",
]

TCL_OSX_COPTS = [
    "-Dftruncate64=ftruncate",
    "-DNO_FSTATFS=1",
]

TCL_LINUX_COPTS = [
    "-DHAVE_STRUCT_STAT64=1",
    "-DHAVE_OPEN64=1",
    "-DHAVE_LSEEK64=1",
    "-DHAVE_TYPE_OFF64_T=1",
    "-DHAVE_GETHOSTBYNAME_R_6=1",
    "-DHAVE_GETHOSTBYNAME_R=1",
    "-DHAVE_GETHOSTBYADDR_R_8=1",
    "-DHAVE_GETHOSTBYADDR_R=1",
]

TCL_COPTS = TCL_BASE_COPTS + select({
        "@platforms//os:osx": TCL_OSX_COPTS,
        "//conditions:default": TCL_LINUX_COPTS,
    })

# tclAlloc uses additional define
cc_library(
    name = "tclAlloc",
    srcs = ["generic/tclAlloc.c"],
    hdrs = glob([
        "generic/*.h",
        "unix/*.h",
    ]),
    includes = ["generic", "unix"],
    copts = TCL_COPTS + [
        "-DUSE_TCLALLOC=0",
    ],
)

# Contains the runtime libraries used in the tcl build rules.
#
# The filegroup is included in the data attribute of rules that require external
# files to run correctly.
filegroup(
    name = "tcl_library_internal",
    srcs = glob([
        "library/**/*",
    ]),
    visibility = ["//visibility:private"],
)

cc_library(
    name = "tclUnixBazelDefaultPaths",
    srcs = [
        "unix/tclBazelDefaultPaths.cc",
    ],
    hdrs = [
        "unix/tclBazelDefaultPaths.h",
    ],
    copts = [
        "-Iunix",
    ],
    deps = [
        "@bazel_tools//tools/cpp/runfiles",
    ],
    data = [
        ":tcl_library_internal",
    ],
)

# tclUnixInit uses additional define
cc_library(
    name = "tclUnixInit",
    srcs = [
        "generic/tcl.h",
        "generic/tclDecls.h",
        "generic/tclInt.h",
        "generic/tclIntDecls.h",
        "generic/tclPort.h",
        "generic/tclTomMathDecls.h",
        "unix/tclUnixInit.c",
    ],
    hdrs = glob([
        "generic/*.h",
        "unix/*.h",
    ]),
    deps = [
        ":tclUnixBazelDefaultPaths",
    ],
    copts = TCL_COPTS + [
        "-DTCL_LIBRARY=\\\"__NONEXISTENT__\\\"",
        "-DTCL_PACKAGE_PATH=\\\"__NONEXISTENT__\\\"",
    ],
    includes = ["generic", "unix"],
)

# pkg-config
cc_library(
    name = "tclPkgConfig",
    srcs = [
        "compat/unistd.h",
        "generic/tclPkgConfig.c",
    ],
    hdrs = glob([
        "generic/*.h",
        "unix/*.h",
    ]),
    copts = [
        "-DCFG_INSTALL_LIBDIR='\"__NONEXISTENT__\"'",
        "-DCFG_INSTALL_BINDIR='\"__NONEXISTENT__\"'",
        "-DCFG_INSTALL_DOCDIR='\"__NONEXISTENT__\"'",
        "-DCFG_INSTALL_INCDIR='\"__NONEXISTENT__\"'",
        "-DCFG_INSTALL_SCRDIR='\"__NONEXISTENT__\"'",
        "-DCFG_RUNTIME_LIBDIR='\"__NONEXISTENT__\"'",
        "-DCFG_RUNTIME_BINDIR='\"__NONEXISTENT__\"'",
        "-DCFG_RUNTIME_DOCDIR='\"__NONEXISTENT__\"'",
        "-DCFG_RUNTIME_INCDIR='\"__NONEXISTENT__\"'",
        "-DCFG_RUNTIME_SCRDIR='\"__NONEXISTENT__\"'",
        "-DTCL_CFGVAL_ENCODING='\"utf-8\"'",
    ],
    includes = [
        "generic/",
        "unix/",
    ],
    deps = [
        ":tclUnixBazelDefaultPaths",
    ]
)

# This is the libtcl
cc_library(
    name = "tcl",
    srcs = [
        "generic/regcomp.c",
        "generic/regerror.c",
        "generic/regexec.c",
        "generic/regfree.c",
        "unix/tclLoadDl.c",
        "libtommath/bn_cutoffs.c",
        "libtommath/bn_mp_add.c",
        "libtommath/bn_mp_add_d.c",
        "libtommath/bn_mp_and.c",
        "libtommath/bn_mp_clamp.c",
        "libtommath/bn_mp_clear.c",
        "libtommath/bn_mp_clear_multi.c",
        "libtommath/bn_mp_cmp.c",
        "libtommath/bn_mp_cmp_d.c",
        "libtommath/bn_mp_cmp_mag.c",
        "libtommath/bn_mp_cnt_lsb.c",
        "libtommath/bn_mp_copy.c",
        "libtommath/bn_mp_count_bits.c",
        "libtommath/bn_mp_div.c",
        "libtommath/bn_mp_div_2.c",
        "libtommath/bn_mp_div_2d.c",
        "libtommath/bn_mp_div_3.c",
        "libtommath/bn_mp_div_d.c",
        "libtommath/bn_mp_exch.c",
        "libtommath/bn_mp_expt_u32.c",
        "libtommath/bn_mp_grow.c",
        "libtommath/bn_mp_init.c",
        "libtommath/bn_mp_init_copy.c",
        "libtommath/bn_mp_init_multi.c",
        "libtommath/bn_mp_init_size.c",
        "libtommath/bn_mp_init_set.c",
        "libtommath/bn_mp_lshd.c",
        "libtommath/bn_mp_mod.c",
        "libtommath/bn_mp_mod_2d.c",
        "libtommath/bn_mp_mul.c",
        "libtommath/bn_mp_mul_2.c",
        "libtommath/bn_mp_mul_2d.c",
        "libtommath/bn_mp_mul_d.c",
        "libtommath/bn_mp_neg.c",
        "libtommath/bn_mp_or.c",
        "libtommath/bn_mp_radix_smap.c",
        "libtommath/bn_mp_radix_size.c",
        "libtommath/bn_mp_read_radix.c",
        "libtommath/bn_mp_rshd.c",
        "libtommath/bn_mp_signed_rsh.c",
        "libtommath/bn_mp_set.c",
        "libtommath/bn_mp_shrink.c",
        "libtommath/bn_mp_sqr.c",
        "libtommath/bn_mp_sqrt.c",
        "libtommath/bn_mp_sub.c",
        "libtommath/bn_mp_sub_d.c",
        "libtommath/bn_mp_to_radix.c",
        "libtommath/bn_mp_to_ubin.c",
        "libtommath/bn_mp_ubin_size.c",
        "libtommath/bn_mp_xor.c",
        "libtommath/bn_mp_zero.c",
        "libtommath/bn_s_mp_add.c",
        "libtommath/bn_s_mp_balance_mul.c",
        "libtommath/bn_s_mp_karatsuba_mul.c",
        "libtommath/bn_s_mp_karatsuba_sqr.c",
        "libtommath/bn_s_mp_mul_digs.c",
        "libtommath/bn_s_mp_mul_digs_fast.c",
        "libtommath/bn_s_mp_reverse.c",
        "libtommath/bn_s_mp_sqr.c",
        "libtommath/bn_s_mp_sqr_fast.c",
        "libtommath/bn_s_mp_sub.c",
        "libtommath/bn_s_mp_toom_mul.c",
        "libtommath/bn_s_mp_toom_sqr.c",
    ] + glob(
        [
            "generic/tcl*.c",
            "unix/tcl*.c",
        ],
        exclude = [
            "generic/tclLoadNone.c",
            "generic/tclPkgConfig.c",
            "generic/tclUniData.c",
            "unix/tclAppInit.c",
            "unix/tclLoad*.c",
            "unix/tclUnixInit.c",
            "unix/tclXtNotify.c",
            "unix/tclXtTest.c",
        ],
    ),
    hdrs = glob([
        "generic/*.h",
        "generic/reg*.c",
        "libtommath/*.h",
    ]),
    copts = TCL_COPTS + [
        "-w",
        "$(STACK_FRAME_UNLIMITED)",  # regexec.c
    ],
    includes = [
        "generic/",
        "libtommath/",
        "unix/",
        "xlib/",
    ],
    linkopts = ["-ldl", "-lpthread"],
    textual_hdrs = glob([
        "generic/*.decls",
    ]) + [
        "generic/tclUniData.c",
    ],
    deps = [
        ":tclAlloc",
        ":tclPkgConfig",
        ":tclUnixInit",
        "@zlib//:zlib",
    ],
    visibility = ["//visibility:public"],
)

# tcl shell
cc_binary(
    name = "tclsh",
    srcs = ["unix/tclAppInit.c"],
    copts = TCL_COPTS + [
        "-w",
    ],
    includes = ["generic", "unix"],
    deps = [
        ":tcl",
        ":tclAlloc",
        ":tclPkgConfig",
        ":tclUnixInit",
    ],
    visibility = ["//visibility:public"],
)
