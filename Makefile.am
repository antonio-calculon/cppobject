#

SUBDIRS = src

pkgconfig_DATA = cppobject.pc

cppobject.pc: cppobject.pc.in config.status
	./config.status --file=$@:$<

.PHONY: listdirs

listdirs:
	@echo "prefix:     '$(prefix)'"
	@echo "datadir:    '$(datadir)'"
	@echo "pkgdatadir: '$(pkgdatadir)'"
	@echo "pkglibdir : '$(pkglibdir)'"
