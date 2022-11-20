.PHONY: all user-install user-uninstall clean

bdf: png2bdf
	./makefont deserted.fontfamily

user-install: bdf
	mkdir -p "${HOME}/.fonts/deserted"
	cp build/*.bdf "${HOME}/.fonts/deserted"
	fc-cache -fv

user-uninstall:
	rm -rf "$HOME/.fonts/deserted"

clean:
	rm -rf build


png2bdf: png2bdf.cpp
