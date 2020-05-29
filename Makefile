#CXX=clang++
CXX=g++
CXX_FLAGS=-O3 -march=native -std=c++14 -DNDEBUG

all: build/glib_hash_table build/stl_unordered_map build/boost_unordered_map build/google_sparse_hash_map build/google_dense_hash_map build/qt_qhash build/python_dict build/ruby_hash \
    build/d3x0r_genhash

build/d3x0r_genhash: src/d3x0r_generic_sparse.cc Makefile dc8a5638fa75520376911b05faf9fc88/genhash_sparse.c src/template.c
	$(CXX) $(CXX_FLAGS) -g -fpermissive -o $@  dc8a5638fa75520376911b05faf9fc88/genhash_sparse.c $< 

build/glib_hash_table: src/glib_hash_table.c Makefile src/template.c
	$(CC) -ggdb -O2 -lm `pkg-config --cflags --libs glib-2.0` src/glib_hash_table.c -o build/glib_hash_table

build/stl_unordered_map: src/stl_unordered_map.cc Makefile src/template.c
	$(CXX) -O2 -lm src/stl_unordered_map.cc -o build/stl_unordered_map -std=c++0x

build/boost_unordered_map: src/boost_unordered_map.cc Makefile src/template.c
	$(CXX) -O2 -lm src/boost_unordered_map.cc -o build/boost_unordered_map

build/google_sparse_hash_map: src/google_sparse_hash_map.cc Makefile src/template.c
	$(CXX) -O2 -lm src/google_sparse_hash_map.cc -o build/google_sparse_hash_map

build/google_dense_hash_map: src/google_dense_hash_map.cc Makefile src/template.c
	$(CXX) -O2 -lm src/google_dense_hash_map.cc -o build/google_dense_hash_map

build/qt_qhash: src/qt_qhash.cc Makefile src/template.c
	$(CXX) -O2 -lm -fPIC `pkg-config --cflags --libs Qt5Core` src/qt_qhash.cc -o build/qt_qhash

build/python_dict: src/python_dict.c Makefile src/template.c
	$(CC) -O2 -lm -I/usr/include/python2.7 -lpython2.7 src/python_dict.c -o build/python_dict

build/ruby_hash: src/ruby_hash.c Makefile src/template.c
	$(CC) -O2 -lm -I/usr/include/ruby-2.7.0 -I /usr/include/ruby-2.7.0/x86_64-linux -lruby src/ruby_hash.c -o build/ruby_hash
