# batup compression

`batup` is a simple compression utility that is designed to achieve good throughput with some data compression in files that contain a fair number of redundant data words.   The compressor works on either binary or text data of almost any structure.  `batup` may be used either by naming files on the command line or streaming with pipes.

There are two utilities provided `batup` and `batdown`.   `batup` and `batdown` are identical except `batdown` defaults to decompression mode, providing the inverse function of `batup`.

```
batup: [parameters] file
	compress or decompress the given file
-c: use stdin/stdout
-d: decompress
```

# design

`batup` exploits the idea that redundant words of data appear in most data. `batup` organizes data into 256kb pages and splits the data along 32bit word boundaries.  Then `batup` indexes each word into a range of 16bit position offsets.  This 'indexing' results in data savings as each words position in the page is represented by only 16 bits of data rather than 32.

# compression metrics

| description | file | original size | batup size | batup time | gzip size | gzip time |
__________________________________________________________________________
| compression | ebat.csv | 17M | 12M | 1.77s | 3M | .7s |
| compression | bigebat.csv | 1.1G | 944M | 3m6.5s | 411M | 1m9.7s |
| decompression | ebat.csv.batz | 17M | 12M | .9s | 3M | .128s |
| decompression | bigebat.csv.batz | 1.1G | 944M | 1m44.6s | 411M | 10.4s |

# getting started

`batup` is built with CMake, therefore it will build and run on almost any environment.   It is portable, although it is using `basename` which may not be installed in all environments. 

## build

``` $ rm -rf build && mkdir -p build && (cd build && cmake -DCMAKE_BUILD_TYPE=RELEASE .. && make -j VERBOSE=1) ```

## run tests

``` $ (cd build && make test) ```

## run batup

``` $ build/batup -?```


