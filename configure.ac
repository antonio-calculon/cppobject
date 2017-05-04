AC_INIT([cppobject], [0.0.0])
AM_INIT_AUTOMAKE

: ${CXXFLAGS:=-g -Wall}

AC_SUBST([pkgconfigdir], ['${libdir}/pkgconfig'])

AC_PROG_CXX
LT_INIT

AC_CONFIG_FILES([ \
  Makefile \
  src/Makefile \
  test/Makefile \
])
AC_OUTPUT
