### Challenges I wrote for UMassCTF-2022

##### Coffee-maker: 1 solve  
```
This challenge was supposed to mimic an attack on an embedded device. Th challenge involved reverse 
engineering a custom lzw compression implementation and implementing a decompressor to retrieve the 
original "firmware". After bypassing some more checks such a magic byte header, a base-64 encoded
password check and a checksum, a buffer overflow vulnerability can be exploited to leak a libc
address using a got leak to get a shell with a ret2libc attack
```
                            
##### Zip-parser: 3 solves
```
This challenge was once again supposed to mimick a real world relevant attack vector, this time on a
file parser. I chose the zip file format for this. Once again there is a buffer overflow due to
insufficient length checks that can be exploited either using a ret2dlresolve exploit or a partial
got overwrite.
```

##### Optimal-vm: 5 solves
```
This challenge involved reverse engineering a custom bytecode-vm. Upon running it against the custom
bytecode binary, it starts slowly printing out the flag, however this quickly slows down and would
not have completed prior to ctf conclusion. The intended solution was to reverse engineer the
bytecode handlers to understand what exactly the bytecode does, and to either optimize the bytecode,
or implement the algorithm in a better way in a language of your choice. (Please excuse the
assembler, I wrote the challenge the night before the ctf :P)
```
