from pwn import *

def add(x, y):
    global fd
    fd.write(p8(0x41))
    fd.write(p8(x))
    fd.write(p8(y))

def be(x, y, z):
    global fd
    fd.write(p8(0x42))
    fd.write(p8(x))
    fd.write(p8(y))
    fd.write(p16(z))

def ll(x, y):
    global fd
    fd.write(p8(0x43))
    fd.write(p8(x))
    fd.write(p64(y))

def LoadArr(x, y):
    global fd
    fd.write(p8(0x44))
    fd.write(p8(x))
    fd.write(p8(y))
    
def jmp(x):
    global fd
    fd.write(p8(0x45))
    fd.write(p16(x))

def toggle(x):
    global fd
    fd.write(p8(0x46))
    fd.write(p8(x))

# if regs[x] is 1, y = 1, else y = 0
def is_true(x, y):
    global fd
    fd.write(p8(0x47))
    fd.write(p8(x))
    fd.write(p8(y))

def sa(i1, i2, i3, i4, i5, i6, i7, i8):
    global fd
    fd.write(p8(0x48))
    fd.write(p64(i1))
    fd.write(p64(i2))
    fd.write(p64(i3))
    fd.write(p64(i4))
    fd.write(p64(i5))
    fd.write(p64(i6))
    fd.write(p64(i7))
    fd.write(p64(i8))

def StoreArr(x, y):
    global fd
    fd.write(p8(0x49))
    fd.write(p8(x))
    fd.write(p8(y))

def finalize():
    global fd
    fd.write(p8(0x50))

def nop():
    global fd
    fd.write(p8(0x51))

fd = open("bin", "wb")

# r0 contains x
# r1 contains i
# r2 contains check
# r3 contains return

# if r0 == r1 -> goto end

# Setup
sa(99823331, 92453972, 43257833, 84387294, 23388939, 88427932, 92940841, 81857454)      #0
ll(7, 0)                        #65
ll(8, 8)                        #75
ll(9, 1)                        #85

# r0 = x; r1 = 0; r2 = true;
ll(2, 1)                        #95

# .l_start
ll(2, 1)                        #105
ll(1, 0)                        #115
LoadArr(0, 7)                   #125

# .s_start
be(0, 1, 141)                   #128

# else i++; toggle(r2)
add(1, 9)                       #133
toggle(2)                       #136
jmp(128)  #jmp start            #138

# .if
# if r2 == true -> r3 = 1, else r3 = 0
is_true(2, 3)                   #141
StoreArr(7, 3)                  #144

add(7, 9)                       #147

be(7, 8, 158)                   #150
jmp(105)                        #155

# end
finalize()                      #158
for i in range(41):
    nop()

off = 200
sa(98543497, 83953266, 94647383, 36529385, 93857672, 93828120, 93538501, 91874252)      
ll(7, 0)                        
ll(8, 8)                        
ll(9, 1)                        
ll(2, 1)                        
ll(2, 1)                        
ll(1, 0)                        
LoadArr(0, 7)                   
be(0, 1, off+141)                   
add(1, 9)                       
toggle(2)                       
jmp(off+128)  #jmp start            
is_true(2, 3)                   
StoreArr(7, 3)                  
add(7, 9)                       
be(7, 8, off+158)                   
jmp(off+105)                        
finalize()                      
for i in range(41):
    nop()

off += 200
sa(93062287, 82349182, 39532753, 96447361, 37592411, 93775265, 92843591, 92533796)      
ll(7, 0)                        
ll(8, 8)                        
ll(9, 1)                        
ll(2, 1)                        
ll(2, 1)                        
ll(1, 0)                        
LoadArr(0, 7)                   
be(0, 1, off+141)                   
add(1, 9)                       
toggle(2)                       
jmp(off+128)  #jmp start            
is_true(2, 3)                   
StoreArr(7, 3)                  
add(7, 9)                       
be(7, 8, off+158)                   
jmp(off+105)                        
finalize()                      
for i in range(41):
    nop()

off += 200
sa(93829563, 72524632, 23764491, 93721292, 28539347, 21648637, 8273324, 83712284)      
ll(7, 0)                        
ll(8, 8)                        
ll(9, 1)                        
ll(2, 1)                        
ll(2, 1)                        
ll(1, 0)                        
LoadArr(0, 7)                   
be(0, 1, off+141)                   
add(1, 9)                       
toggle(2)                       
jmp(off+128)  #jmp start            
is_true(2, 3)                   
StoreArr(7, 3)                  
add(7, 9)                       
be(7, 8, off+158)                   
jmp(off+105)                        
finalize()                      
for i in range(41):
    nop()

off += 200
sa(837284053, 910284734, 837462985, 938102966, 183740583, 192048575, 928374582, 837462816)      
ll(7, 0)                        
ll(8, 8)                        
ll(9, 1)                        
ll(2, 1)                        
ll(2, 1)                        
ll(1, 0)                        
LoadArr(0, 7)                   
be(0, 1, off+141)                   
add(1, 9)                       
toggle(2)                       
jmp(off+128)  #jmp start            
is_true(2, 3)                   
StoreArr(7, 3)                  
add(7, 9)                       
be(7, 8, off+158)                   
jmp(off+105)                        
finalize()                      
for i in range(41):
    nop()

off += 200
sa(827394827, 438293844, 283940592, 827384956, 948302388, 928172931, 940382916, 483920182)      
ll(7, 0)                        
ll(8, 8)                        
ll(9, 1)                        
ll(2, 1)                        
ll(2, 1)                        
ll(1, 0)                        
LoadArr(0, 7)                   
be(0, 1, off+141)                   
add(1, 9)                       
toggle(2)                       
jmp(off+128)  #jmp start            
is_true(2, 3)                   
StoreArr(7, 3)                  
add(7, 9)                       
be(7, 8, off+158)                   
jmp(off+105)                        
finalize()                      
for i in range(41):
    nop()

off += 200
sa(8392039481, 9283746598, 8273849583, 1728394828, 8273619241, 1728394853, 1728394858, 8293847564)      
ll(7, 0)                        
ll(8, 8)                        
ll(9, 1)                        
ll(2, 1)                        
ll(2, 1)                        
ll(1, 0)                        
LoadArr(0, 7)                   
be(0, 1, off+141)                   
add(1, 9)                       
toggle(2)                       
jmp(off+128)  #jmp start            
is_true(2, 3)                   
StoreArr(7, 3)                  
add(7, 9)                       
be(7, 8, off+158)                   
jmp(off+105)                        
finalize()                      
for i in range(41):
    nop()

off += 200
sa(8493827191, 8572918371, 7489302182, 7583920382, 3758392051, 8293847501, 7283940511, 6739203951)      
ll(7, 0)                        
ll(8, 8)                        
ll(9, 1)                        
ll(2, 1)                        
ll(2, 1)                        
ll(1, 0)                        
LoadArr(0, 7)                   
be(0, 1, off+141)                   
add(1, 9)                       
toggle(2)                       
jmp(off+128)  #jmp start            
is_true(2, 3)                   
StoreArr(7, 3)                  
add(7, 9)                       
be(7, 8, off+158)                   
jmp(off+105)                        
finalize()                      
for i in range(41):
    nop()

off += 200
sa(83920192837, 72891920396, 48392019387, 57182930574, 49173920164, 94827618202, 12345678902, 98765432100)      
ll(7, 0)                        
ll(8, 8)                        
ll(9, 1)                        
ll(2, 1)                        
ll(2, 1)                        
ll(1, 0)                        
LoadArr(0, 7)                   
be(0, 1, off+141)                   
add(1, 9)                       
toggle(2)                       
jmp(off+128)  #jmp start            
is_true(2, 3)                   
StoreArr(7, 3)                  
add(7, 9)                       
be(7, 8, off+158)                   
jmp(off+105)                        
finalize()                      
for i in range(41):
    nop()

off += 200
sa(84931029373, 38291029372, 17384903281, 74839209588, 57839201921, 48293857197, 58293059106, 382193049574)      
ll(7, 0)                        
ll(8, 8)                        
ll(9, 1)                        
ll(2, 1)                        
ll(2, 1)                        
ll(1, 0)                        
LoadArr(0, 7)                   
be(0, 1, off+141)                   
add(1, 9)                       
toggle(2)                       
jmp(off+128)  #jmp start            
is_true(2, 3)                   
StoreArr(7, 3)                  
add(7, 9)                       
be(7, 8, off+158)                   
jmp(off+105)                        
finalize()                      
for i in range(41):
    nop()

off += 200
sa(335437119853206641, 325480512983128082, 937531610318839252, 814169737621380282, 587070023501987331, 423979435513392471, 885546676506441821, 997472143202148691)      
ll(7, 0)                        
ll(8, 8)                        
ll(9, 1)                        
ll(2, 1)                        
ll(2, 1)                        
ll(1, 0)                        
LoadArr(0, 7)                   
be(0, 1, off+141)                   
add(1, 9)                       
toggle(2)                       
jmp(off+128)  #jmp start            
is_true(2, 3)                   
StoreArr(7, 3)                  
add(7, 9)                       
be(7, 8, off+158)                   
jmp(off+105)                        
finalize()                      
for i in range(41):
    nop()

off += 200
sa(187403773485712861, 187403773485712861, 211248426165462132, 930226715275785722, 673370437605789491, 508416567344842111, 50535031016693672, 873439923407388862)      
ll(7, 0)                        
ll(8, 8)                        
ll(9, 1)                        
ll(2, 1)                        
ll(2, 1)                        
ll(1, 0)                        
LoadArr(0, 7)                   
be(0, 1, off+141)                   
add(1, 9)                       
toggle(2)                       
jmp(off+128)  #jmp start            
is_true(2, 3)                   
StoreArr(7, 3)                  
add(7, 9)                       
be(7, 8, off+158)                   
jmp(off+105)                        
finalize()                      
for i in range(41):
    nop()

off += 200
sa(763720582027213331, 386204768268841531, 873472638679046852, 432603994150914472, 876535849129264021, 700270231179594541, 89968083883491912, 195730881813012362)      
ll(7, 0)                        
ll(8, 8)                        
ll(9, 1)                        
ll(2, 1)                        
ll(2, 1)                        
ll(1, 0)                        
LoadArr(0, 7)                   
be(0, 1, off+141)                   
add(1, 9)                       
toggle(2)                       
jmp(off+128)  #jmp start            
is_true(2, 3)                   
StoreArr(7, 3)                  
add(7, 9)                       
be(7, 8, off+158)                   
jmp(off+105)                        
finalize()                      
for i in range(41):
    nop()

off += 200
sa(45983610447688611, 771917474352598482, 315895669124786602, 439806188377993931, 620780798137176781, 131845650966886302, 118007013644857671, 77717712212157851)      
ll(7, 0)                        
ll(8, 8)                        
ll(9, 1)                        
ll(2, 1)                        
ll(2, 1)                        
ll(1, 0)                        
LoadArr(0, 7)                   
be(0, 1, off+141)                   
add(1, 9)                       
toggle(2)                       
jmp(off+128)  #jmp start            
is_true(2, 3)                   
StoreArr(7, 3)                  
add(7, 9)                       
be(7, 8, off+158)                   
jmp(off+105)                        
finalize()                      
for i in range(41):
    nop()

off += 200
sa(366949472621257821, 422387027626545062, 57958949816059662, 252780462218126812, 491327372818783442, 488025816006703461, 718304433452191, 733515456481577172)      
ll(7, 0)                        
ll(8, 8)                        
ll(9, 1)                        
ll(2, 1)                        
ll(2, 1)                        
ll(1, 0)                        
LoadArr(0, 7)                   
be(0, 1, off+141)                   
add(1, 9)                       
toggle(2)                       
jmp(off+128)  #jmp start            
is_true(2, 3)                   
StoreArr(7, 3)                  
add(7, 9)                       
be(7, 8, off+158)                   
jmp(off+105)                        
finalize()                      
for i in range(41):
    nop()

off += 200
sa(534919451316784151, 115118668191861272, 741592744287315172, 116975971791105282, 531272504940036782, 168652805448585082, 778554733206005751, 701155445180560402)      
ll(7, 0)                        
ll(8, 8)                        
ll(9, 1)                        
ll(2, 1)                        
ll(2, 1)                        
ll(1, 0)                        
LoadArr(0, 7)                   
be(0, 1, off+141)                   
add(1, 9)                       
toggle(2)                       
jmp(off+128)  #jmp start            
is_true(2, 3)                   
StoreArr(7, 3)                  
add(7, 9)                       
be(7, 8, off+158)                   
jmp(off+105)                        
finalize()                      
for i in range(41):
    nop()

fd.close()
