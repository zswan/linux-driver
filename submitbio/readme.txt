1.How to use those drivers:

insmod blk.ko
insmod submit.ko
cd /sys/class/testdriver/testdriver0
echo 1 > writeblk

2. What's those drivers?

blockdriver.c -- a simple block device driver
submitbio.c -- create a bio and init it, and submit bio to block layer.
               from this driver, you can track many useful information
               for submit_bio interface.
testdriver.c -- trigger read and write bio pages.

Test log:

root@viwan-emmc:/sys/class/testdriver/testdriver0# echo 1 > writeblk 
root@viwan-emmc:/sys/class/testdriver/testdriver0# ddd
[  304.624667] 0x66 ,0x66 ,0x66 ,0x66 ,0x66 ,0x66 ,0x66 ,0x66 ,0x66 ,
[ 2612.605182] TESTDRIVER: testdriver_cleanup_module!
[ 2681.269016] TESTDRIVER:Ok to register testdriver device 201!
[ 2696.850199] 1.SUBMITIO:
[ 2696.850209] bio->bi_max_vecs:16
[ 2696.850211] bio->bi_vcnt:0
[ 2696.850214] bio->bi_iter.bi_sector:0
[ 2696.850216] 3.SUBMITIO:
[ 2696.850218] bio->bi_max_vecs:16
[ 2696.850220] bio->bi_vcnt:1
[ 2696.850221] bio->bi_iter.bi_sector:0
[ 2696.850223] 3.SUBMITIO:
[ 2696.850225] bio->bi_max_vecs:16
[ 2696.850226] bio->bi_vcnt:2
[ 2696.850228] bio->bi_iter.bi_sector:0
[ 2696.850229] 3.SUBMITIO:
[ 2696.850231] bio->bi_max_vecs:16
[ 2696.850233] bio->bi_vcnt:3
[ 2696.850234] bio->bi_iter.bi_sector:0
[ 2696.850236] 3.SUBMITIO:
[ 2696.850237] bio->bi_max_vecs:16
[ 2696.850239] bio->bi_vcnt:4
[ 2696.850241] bio->bi_iter.bi_sector:0
[ 2696.850242] 3.SUBMITIO:
[ 2696.850244] bio->bi_max_vecs:16
[ 2696.850246] bio->bi_vcnt:5
[ 2696.850247] bio->bi_iter.bi_sector:0
[ 2696.850249] 3.SUBMITIO:
[ 2696.850250] bio->bi_max_vecs:16
[ 2696.850252] bio->bi_vcnt:6
[ 2696.850254] bio->bi_iter.bi_sector:0
[ 2696.850255] 3.SUBMITIO:
[ 2696.850257] bio->bi_max_vecs:16
[ 2696.850258] bio->bi_vcnt:7
[ 2696.850260] bio->bi_iter.bi_sector:0
[ 2696.850262] 3.SUBMITIO:
[ 2696.850263] bio->bi_max_vecs:16
[ 2696.850265] bio->bi_vcnt:8
[ 2696.850266] bio->bi_iter.bi_sector:0
[ 2696.850268] 3.SUBMITIO:
[ 2696.850270] bio->bi_max_vecs:16
[ 2696.850271] bio->bi_vcnt:9
[ 2696.850273] bio->bi_iter.bi_sector:0
[ 2696.850274] 3.SUBMITIO:
[ 2696.850276] bio->bi_max_vecs:16
[ 2696.850278] bio->bi_vcnt:10
[ 2696.850279] bio->bi_iter.bi_sector:0
[ 2696.850281] 3.SUBMITIO:
[ 2696.850282] bio->bi_max_vecs:16
[ 2696.850284] bio->bi_vcnt:11
[ 2696.850286] bio->bi_iter.bi_sector:0
[ 2696.850287] 3.SUBMITIO:
[ 2696.850289] bio->bi_max_vecs:16
[ 2696.850290] bio->bi_vcnt:12
[ 2696.850292] bio->bi_iter.bi_sector:0
[ 2696.850293] 3.SUBMITIO:
[ 2696.850295] bio->bi_max_vecs:16
[ 2696.850297] bio->bi_vcnt:13
[ 2696.850298] bio->bi_iter.bi_sector:0
[ 2696.850300] 3.SUBMITIO:
[ 2696.850301] bio->bi_max_vecs:16
[ 2696.850303] bio->bi_vcnt:14
[ 2696.850305] bio->bi_iter.bi_sector:0
[ 2696.850306] 3.SUBMITIO:
[ 2696.850308] bio->bi_max_vecs:16
[ 2696.850309] bio->bi_vcnt:15
[ 2696.850311] bio->bi_iter.bi_sector:0
[ 2696.850312] 3.SUBMITIO:
[ 2696.850314] bio->bi_max_vecs:16
[ 2696.850316] bio->bi_vcnt:16
[ 2696.850317] bio->bi_iter.bi_sector:0
[ 2696.850320] 4.SUBMITIO: bio->bi_max_vecs = 16,		bi_sizes = 65536, bio->bi_iter.bi_size = 65536n
[ 2696.850326] bash(3495): WRITE block 0 on simp_blkdev (128 sectors)
[ 2696.850396] BLKDEV:Write-sector:0--size = 4096--
[ 2696.850403] BLKDEV:source, req->buffer:
[ 2696.850410] 0x66 ,0x66 ,0x66 ,0x66 ,0x66 ,0x66 ,0x66 ,0x66 ,0x66 ,0x66 ,
[ 2696.850459] 0x66 ,0x66 ,0x66 ,0x66 ,0x66 ,0x66 ,0x66 ,0x66 ,0x66 ,0x66 ,
[ 2696.850473] 0x66 ,0x66 ,0x66 ,0x66 ,0x66 ,0x66 ,0x66 ,0x66 ,0x66 ,0x66 ,
[ 2696.850481] 0x66 ,0x66 ,0x66 ,0x66 ,0x66 ,0x66 ,0x66 ,0x66 ,0x66 ,0x66 ,
[ 2696.850493] BLKDEV:dest, simp_blkdev_data:
[ 2696.850494] 0x66 ,0x66 ,0x66 ,0x66 ,0x66 ,0x66 ,0x66 ,0x66 ,0x66 ,0x66 ,
[ 2696.850503] 0x66 ,0x66 ,0x66 ,0x66 ,0x66 ,0x66 ,0x66 ,0x66 ,0x66 ,0x66 ,
[ 2696.850511] 0x66 ,0x66 ,0x66 ,0x66 ,0x66 ,0x66 ,0x66 ,0x66 ,0x66 ,0x66 ,
[ 2696.850520] 0x66 ,0x66 ,0x66 ,0x66 ,0x66 ,0x66 ,0x66 ,0x66 ,0x66 ,0x66 ,
[ 2696.850531] BLKDEV:Write-sector:8--size = 4096--
[ 2696.850534] BLKDEV:source, req->buffer:
[ 2696.850535] 0x66 ,0x66 ,0x66 ,0x66 ,0x66 ,0x66 ,0x66 ,0x66 ,0x66 ,0x66 ,
[ 2696.850544] 0x66 ,0x66 ,0x66 ,0x66 ,0x66 ,0x66 ,0x66 ,0x66 ,0x66 ,0x66 ,
[ 2696.850552] 0x66 ,0x66 ,0x66 ,0x66 ,0x66 ,0x66 ,0x66 ,0x66 ,0x66 ,0x66 ,
[ 2696.850560] 0x66 ,0x66 ,0x66 ,0x66 ,0x66 ,0x66 ,0x66 ,0x66 ,0x66 ,0x66 ,
[ 2696.850570] BLKDEV:dest, simp_blkdev_data:
[ 2696.850572] 0x66 ,0x66 ,0x66 ,0x66 ,0x66 ,0x66 ,0x66 ,0x66 ,0x66 ,0x66 ,
[ 2696.850580] 0x66 ,0x66 ,0x66 ,0x66 ,0x66 ,0x66 ,0x66 ,0x66 ,0x66 ,0x66 ,
[ 2696.850588] 0x66 ,0x66 ,0x66 ,0x66 ,0x66 ,0x66 ,0x66 ,0x66 ,0x66 ,0x66 ,
[ 2696.850597] 0x66 ,0x66 ,0x66 ,0x66 ,0x66 ,0x66 ,0x66 ,0x66 ,0x66 ,0x66 ,
[ 2696.850606] BLKDEV:Write-sector:16--size = 4096--
[ 2696.850608] BLKDEV:source, req->buffer:
[ 2696.850609] 0x66 ,0x66 ,0x66 ,0x66 ,0x66 ,0x66 ,0x66 ,0x66 ,0x66 ,0x66 ,
[ 2696.850618] 0x66 ,0x66 ,0x66 ,0x66 ,0x66 ,0x66 ,0x66 ,0x66 ,0x66 ,0x66 ,
[ 2696.850626] 0x66 ,0x66 ,0x66 ,0x66 ,0x66 ,0x66 ,0x66 ,0x66 ,0x66 ,0x66 ,
[ 2696.850634] 0x66 ,0x66 ,0x66 ,0x66 ,0x66 ,0x66 ,0x66 ,0x66 ,0x66 ,0x66 ,
[ 2696.850644] BLKDEV:dest, simp_blkdev_data:
[ 2696.850646] 0x66 ,0x66 ,0x66 ,0x66 ,0x66 ,0x66 ,0x66 ,0x66 ,0x66 ,0x66 ,
[ 2696.850654] 0x66 ,0x66 ,0x66 ,0x66 ,0x66 ,0x66 ,0x66 ,0x66 ,0x66 ,0x66 ,
[ 2696.850684] 0x66 ,0x66 ,0x66 ,0x66 ,0x66 ,0x66 ,0x66 ,0x66 ,0x66 ,0x66 ,
[ 2696.850706] 0x66 ,0x66 ,0x66 ,0x66 ,0x66 ,0x66 ,0x66 ,0x66 ,0x66 ,0x66 ,
[ 2696.850715] BLKDEV:Write-sector:24--size = 4096--
[ 2696.850717] BLKDEV:source, req->buffer:
[ 2696.850718] 0x66 ,0x66 ,0x66 ,0x66 ,0x66 ,0x66 ,0x66 ,0x66 ,0x66 ,0x66 ,
[ 2696.850726] 0x66 ,0x66 ,0x66 ,0x66 ,0x66 ,0x66 ,0x66 ,0x66 ,0x66 ,0x66 ,
[ 2696.850735] 0x66 ,0x66 ,0x66 ,0x66 ,0x66 ,0x66 ,0x66 ,0x66 ,0x66 ,0x66 ,
[ 2696.850744] 0x66 ,0x66 ,0x66 ,0x66 ,0x66 ,0x66 ,0x66 ,0x66 ,0x66 ,0x66 ,
[ 2696.850754] BLKDEV:dest, simp_blkdev_data:
[ 2696.850755] 0x66 ,0x66 ,0x66 ,0x66 ,0x66 ,0x66 ,0x66 ,0x66 ,0x66 ,0x66 ,
[ 2696.850763] 0x66 ,0x66 ,0x66 ,0x66 ,0x66 ,0x66 ,0x66 ,0x66 ,0x66 ,0x66 ,
[ 2696.850771] 0x66 ,0x66 ,0x66 ,0x66 ,0x66 ,0x66 ,0x66 ,0x66 ,0x66 ,0x66 ,
[ 2696.850779] 0x66 ,0x66 ,0x66 ,0x66 ,0x66 ,0x66 ,0x66 ,0x66 ,0x66 ,0x66 ,
[ 2696.850804] BLKDEV:Write-sector:32--size = 4096--
[ 2696.850806] BLKDEV:source, req->buffer:
[ 2696.850807] 0x66 ,0x66 ,0x66 ,0x66 ,0x66 ,0x66 ,0x66 ,0x66 ,0x66 ,0x66 ,
[ 2696.850816] 0x66 ,0x66 ,0x66 ,0x66 ,0x66 ,0x66 ,0x66 ,0x66 ,0x66 ,0x66 ,
[ 2696.850829] 0x66 ,0x66 ,0x66 ,0x66 ,0x66 ,0x66 ,0x66 ,0x66 ,0x66 ,0x66 ,
[ 2696.850839] 0x66 ,0x66 ,0x66 ,0x66 ,0x66 ,0x66 ,0x66 ,0x66 ,0x66 ,0x66 ,
[ 2696.850848] BLKDEV:dest, simp_blkdev_data:
[ 2696.850850] 0x66 ,0x66 ,0x66 ,0x66 ,0x66 ,0x66 ,0x66 ,0x66 ,0x66 ,0x66 ,
[ 2696.850858] 0x66 ,0x66 ,0x66 ,0x66 ,0x66 ,0x66 ,0x66 ,0x66 ,0x66 ,0x66 ,
[ 2696.850865] 0x66 ,0x66 ,0x66 ,0x66 ,0x66 ,0x66 ,0x66 ,0x66 ,0x66 ,0x66 ,
[ 2696.850873] 0x66 ,0x66 ,0x66 ,0x66 ,0x66 ,0x66 ,0x66 ,0x66 ,0x66 ,0x66 ,
[ 2696.850887] BLKDEV:Write-sector:40--size = 4096--
[ 2696.850894] BLKDEV:source, req->buffer:
[ 2696.850896] 0x66 ,0x66 ,0x66 ,0x66 ,0x66 ,0x66 ,0x66 ,0x66 ,0x66 ,0x66 ,
[ 2696.850904] 0x66 ,0x66 ,0x66 ,0x66 ,0x66 ,0x66 ,0x66 ,0x66 ,0x66 ,0x66 ,
[ 2696.850912] 0x66 ,0x66 ,0x66 ,0x66 ,0x66 ,0x66 ,0x66 ,0x66 ,0x66 ,0x66 ,
[ 2696.850924] 0x66 ,0x66 ,0x66 ,0x66 ,0x66 ,0x66 ,0x66 ,0x66 ,0x66 ,0x66 ,
[ 2696.850936] BLKDEV:dest, simp_blkdev_data:
[ 2696.850937] 0x66 ,0x66 ,0x66 ,0x66 ,0x66 ,0x66 ,0x66 ,0x66 ,0x66 ,0x66 ,
[ 2696.850945] 0x66 ,0x66 ,0x66 ,0x66 ,0x66 ,0x66 ,0x66 ,0x66 ,0x66 ,0x66 ,
[ 2696.850953] 0x66 ,0x66 ,0x66 ,0x66 ,0x66 ,0x66 ,0x66 ,0x66 ,0x66 ,0x66 ,
[ 2696.850960] 0x66 ,0x66 ,0x66 ,0x66 ,0x66 ,0x66 ,0x66 ,0x66 ,0x66 ,0x66 ,
[ 2696.850969] BLKDEV:Write-sector:48--size = 4096--
[ 2696.850970] BLKDEV:source, req->buffer:
[ 2696.850972] 0x66 ,0x66 ,0x66 ,0x66 ,0x66 ,0x66 ,0x66 ,0x66 ,0x66 ,0x66 ,
[ 2696.850979] 0x66 ,0x66 ,0x66 ,0x66 ,0x66 ,0x66 ,0x66 ,0x66 ,0x66 ,0x66 ,
[ 2696.850987] 0x66 ,0x66 ,0x66 ,0x66 ,0x66 ,0x66 ,0x66 ,0x66 ,0x66 ,0x66 ,
[ 2696.850995] 0x66 ,0x66 ,0x66 ,0x66 ,0x66 ,0x66 ,0x66 ,0x66 ,0x66 ,0x66 ,
[ 2696.851004] BLKDEV:dest, simp_blkdev_data:
[ 2696.851006] 0x66 ,0x66 ,0x66 ,0x66 ,0x66 ,0x66 ,0x66 ,0x66 ,0x66 ,0x66 ,
[ 2696.851013] 0x66 ,0x66 ,0x66 ,0x66 ,0x66 ,0x66 ,0x66 ,0x66 ,0x66 ,0x66 ,
[ 2696.851021] 0x66 ,0x66 ,0x66 ,0x66 ,0x66 ,0x66 ,0x66 ,0x66 ,0x66 ,0x66 ,
[ 2696.851029] 0x66 ,0x66 ,0x66 ,0x66 ,0x66 ,0x66 ,0x66 ,0x66 ,0x66 ,0x66 ,
[ 2696.851037] BLKDEV:Write-sector:56--size = 4096--
[ 2696.851039] BLKDEV:source, req->buffer:
[ 2696.851040] 0x66 ,0x66 ,0x66 ,0x66 ,0x66 ,0x66 ,0x66 ,0x66 ,0x66 ,0x66 ,
[ 2696.851048] 0x66 ,0x66 ,0x66 ,0x66 ,0x66 ,0x66 ,0x66 ,0x66 ,0x66 ,0x66 ,
[ 2696.851055] 0x66 ,0x66 ,0x66 ,0x66 ,0x66 ,0x66 ,0x66 ,0x66 ,0x66 ,0x66 ,
[ 2696.851063] 0x66 ,0x66 ,0x66 ,0x66 ,0x66 ,0x66 ,0x66 ,0x66 ,0x66 ,0x66 ,
[ 2696.851073] BLKDEV:dest, simp_blkdev_data:
[ 2696.851074] 0x66 ,0x66 ,0x66 ,0x66 ,0x66 ,0x66 ,0x66 ,0x66 ,0x66 ,0x66 ,
[ 2696.851082] 0x66 ,0x66 ,0x66 ,0x66 ,0x66 ,0x66 ,0x66 ,0x66 ,0x66 ,0x66 ,
[ 2696.851090] 0x66 ,0x66 ,0x66 ,0x66 ,0x66 ,0x66 ,0x66 ,0x66 ,0x66 ,0x66 ,
[ 2696.851097] 0x66 ,0x66 ,0x66 ,0x66 ,0x66 ,0x66 ,0x66 ,0x66 ,0x66 ,0x66 ,
[ 2696.851106] BLKDEV:Write-sector:64--size = 4096--
[ 2696.851107] BLKDEV:source, req->buffer:
[ 2696.851109] 0x66 ,0x66 ,0x66 ,0x66 ,0x66 ,0x66 ,0x66 ,0x66 ,0x66 ,0x66 ,
[ 2696.851116] 0x66 ,0x66 ,0x66 ,0x66 ,0x66 ,0x66 ,0x66 ,0x66 ,0x66 ,0x66 ,
[ 2696.851124] 0x66 ,0x66 ,0x66 ,0x66 ,0x66 ,0x66 ,0x66 ,0x66 ,0x66 ,0x66 ,
[ 2696.851131] 0x66 ,0x66 ,0x66 ,0x66 ,0x66 ,0x66 ,0x66 ,0x66 ,0x66 ,0x66 ,
[ 2696.851141] BLKDEV:dest, simp_blkdev_data:
[ 2696.851142] 0x66 ,0x66 ,0x66 ,0x66 ,0x66 ,0x66 ,0x66 ,0x66 ,0x66 ,0x66 ,
[ 2696.851150] 0x66 ,0x66 ,0x66 ,0x66 ,0x66 ,0x66 ,0x66 ,0x66 ,0x66 ,0x66 ,
[ 2696.851157] 0x66 ,0x66 ,0x66 ,0x66 ,0x66 ,0x66 ,0x66 ,0x66 ,0x66 ,0x66 ,
[ 2696.851165] 0x66 ,0x66 ,0x66 ,0x66 ,0x66 ,0x66 ,0x66 ,0x66 ,0x66 ,0x66 ,
[ 2696.851173] BLKDEV:Write-sector:72--size = 4096--
[ 2696.851175] BLKDEV:source, req->buffer:
[ 2696.851176] 0x66 ,0x66 ,0x66 ,0x66 ,0x66 ,0x66 ,0x66 ,0x66 ,0x66 ,0x66 ,
[ 2696.851184] 0x66 ,0x66 ,0x66 ,0x66 ,0x66 ,0x66 ,0x66 ,0x66 ,0x66 ,0x66 ,
[ 2696.851192] 0x66 ,0x66 ,0x66 ,0x66 ,0x66 ,0x66 ,0x66 ,0x66 ,0x66 ,0x66 ,
[ 2696.851199] 0x66 ,0x66 ,0x66 ,0x66 ,0x66 ,0x66 ,0x66 ,0x66 ,0x66 ,0x66 ,
[ 2696.851208] BLKDEV:dest, simp_blkdev_data:
[ 2696.851210] 0x66 ,0x66 ,0x66 ,0x66 ,0x66 ,0x66 ,0x66 ,0x66 ,0x66 ,0x66 ,
[ 2696.851217] 0x66 ,0x66 ,0x66 ,0x66 ,0x66 ,0x66 ,0x66 ,0x66 ,0x66 ,0x66 ,
[ 2696.851225] 0x66 ,0x66 ,0x66 ,0x66 ,0x66 ,0x66 ,0x66 ,0x66 ,0x66 ,0x66 ,
[ 2696.851233] 0x66 ,0x66 ,0x66 ,0x66 ,0x66 ,0x66 ,0x66 ,0x66 ,0x66 ,0x66 ,
[ 2696.851241] BLKDEV:Write-sector:80--size = 4096--
[ 2696.851242] BLKDEV:source, req->buffer:
[ 2696.851244] 0x66 ,0x66 ,0x66 ,0x66 ,0x66 ,0x66 ,0x66 ,0x66 ,0x66 ,0x66 ,
[ 2696.851252] 0x66 ,0x66 ,0x66 ,0x66 ,0x66 ,0x66 ,0x66 ,0x66 ,0x66 ,0x66 ,
[ 2696.851259] 0x66 ,0x66 ,0x66 ,0x66 ,0x66 ,0x66 ,0x66 ,0x66 ,0x66 ,0x66 ,
[ 2696.851267] 0x66 ,0x66 ,0x66 ,0x66 ,0x66 ,0x66 ,0x66 ,0x66 ,0x66 ,0x66 ,
[ 2696.851276] BLKDEV:dest, simp_blkdev_data:
[ 2696.851277] 0x66 ,0x66 ,0x66 ,0x66 ,0x66 ,0x66 ,0x66 ,0x66 ,0x66 ,0x66 ,
[ 2696.851285] 0x66 ,0x66 ,0x66 ,0x66 ,0x66 ,0x66 ,0x66 ,0x66 ,0x66 ,0x66 ,
[ 2696.851292] 0x66 ,0x66 ,0x66 ,0x66 ,0x66 ,0x66 ,0x66 ,0x66 ,0x66 ,0x66 ,
[ 2696.851300] 0x66 ,0x66 ,0x66 ,0x66 ,0x66 ,0x66 ,0x66 ,0x66 ,0x66 ,0x66 ,
[ 2696.851308] BLKDEV:Write-sector:88--size = 4096--
[ 2696.851310] BLKDEV:source, req->buffer:
[ 2696.851311] 0x66 ,0x66 ,0x66 ,0x66 ,0x66 ,0x66 ,0x66 ,0x66 ,0x66 ,0x66 ,
[ 2696.851319] 0x66 ,0x66 ,0x66 ,0x66 ,0x66 ,0x66 ,0x66 ,0x66 ,0x66 ,0x66 ,
[ 2696.851327] 0x66 ,0x66 ,0x66 ,0x66 ,0x66 ,0x66 ,0x66 ,0x66 ,0x66 ,0x66 ,
[ 2696.851334] 0x66 ,0x66 ,0x66 ,0x66 ,0x66 ,0x66 ,0x66 ,0x66 ,0x66 ,0x66 ,
[ 2696.851343] BLKDEV:dest, simp_blkdev_data:
[ 2696.851345] 0x66 ,0x66 ,0x66 ,0x66 ,0x66 ,0x66 ,0x66 ,0x66 ,0x66 ,0x66 ,
[ 2696.851352] 0x66 ,0x66 ,0x66 ,0x66 ,0x66 ,0x66 ,0x66 ,0x66 ,0x66 ,0x66 ,
[ 2696.851360] 0x66 ,0x66 ,0x66 ,0x66 ,0x66 ,0x66 ,0x66 ,0x66 ,0x66 ,0x66 ,
[ 2696.851368] 0x66 ,0x66 ,0x66 ,0x66 ,0x66 ,0x66 ,0x66 ,0x66 ,0x66 ,0x66 ,
[ 2696.851376] BLKDEV:Write-sector:96--size = 4096--
[ 2696.851377] BLKDEV:source, req->buffer:
[ 2696.851379] 0x66 ,0x66 ,0x66 ,0x66 ,0x66 ,0x66 ,0x66 ,0x66 ,0x66 ,0x66 ,
[ 2696.851386] 0x66 ,0x66 ,0x66 ,0x66 ,0x66 ,0x66 ,0x66 ,0x66 ,0x66 ,0x66 ,
[ 2696.851394] 0x66 ,0x66 ,0x66 ,0x66 ,0x66 ,0x66 ,0x66 ,0x66 ,0x66 ,0x66 ,
[ 2696.851402] 0x66 ,0x66 ,0x66 ,0x66 ,0x66 ,0x66 ,0x66 ,0x66 ,0x66 ,0x66 ,
[ 2696.851411] BLKDEV:dest, simp_blkdev_data:
[ 2696.851412] 0x66 ,0x66 ,0x66 ,0x66 ,0x66 ,0x66 ,0x66 ,0x66 ,0x66 ,0x66 ,
[ 2696.851420] 0x66 ,0x66 ,0x66 ,0x66 ,0x66 ,0x66 ,0x66 ,0x66 ,0x66 ,0x66 ,
[ 2696.851428] 0x66 ,0x66 ,0x66 ,0x66 ,0x66 ,0x66 ,0x66 ,0x66 ,0x66 ,0x66 ,
[ 2696.851435] 0x66 ,0x66 ,0x66 ,0x66 ,0x66 ,0x66 ,0x66 ,0x66 ,0x66 ,0x66 ,
[ 2696.851443] BLKDEV:Write-sector:104--size = 4096--
[ 2696.851445] BLKDEV:source, req->buffer:
[ 2696.851447] 0x66 ,0x66 ,0x66 ,0x66 ,0x66 ,0x66 ,0x66 ,0x66 ,0x66 ,0x66 ,
[ 2696.851454] 0x66 ,0x66 ,0x66 ,0x66 ,0x66 ,0x66 ,0x66 ,0x66 ,0x66 ,0x66 ,
[ 2696.851462] 0x66 ,0x66 ,0x66 ,0x66 ,0x66 ,0x66 ,0x66 ,0x66 ,0x66 ,0x66 ,
[ 2696.851469] 0x66 ,0x66 ,0x66 ,0x66 ,0x66 ,0x66 ,0x66 ,0x66 ,0x66 ,0x66 ,
[ 2696.851479] BLKDEV:dest, simp_blkdev_data:
[ 2696.851480] 0x66 ,0x66 ,0x66 ,0x66 ,0x66 ,0x66 ,0x66 ,0x66 ,0x66 ,0x66 ,
[ 2696.851488] 0x66 ,0x66 ,0x66 ,0x66 ,0x66 ,0x66 ,0x66 ,0x66 ,0x66 ,0x66 ,
[ 2696.851495] 0x66 ,0x66 ,0x66 ,0x66 ,0x66 ,0x66 ,0x66 ,0x66 ,0x66 ,0x66 ,
[ 2696.851503] 0x66 ,0x66 ,0x66 ,0x66 ,0x66 ,0x66 ,0x66 ,0x66 ,0x66 ,0x66 ,
[ 2696.851511] BLKDEV:Write-sector:112--size = 4096--
[ 2696.851513] BLKDEV:source, req->buffer:
[ 2696.851514] 0x66 ,0x66 ,0x66 ,0x66 ,0x66 ,0x66 ,0x66 ,0x66 ,0x66 ,0x66 ,
[ 2696.851522] 0x66 ,0x66 ,0x66 ,0x66 ,0x66 ,0x66 ,0x66 ,0x66 ,0x66 ,0x66 ,
[ 2696.851530] 0x66 ,0x66 ,0x66 ,0x66 ,0x66 ,0x66 ,0x66 ,0x66 ,0x66 ,0x66 ,
[ 2696.851537] 0x66 ,0x66 ,0x66 ,0x66 ,0x66 ,0x66 ,0x66 ,0x66 ,0x66 ,0x66 ,
[ 2696.851547] BLKDEV:dest, simp_blkdev_data:
[ 2696.851549] 0x66 ,0x66 ,0x66 ,0x66 ,0x66 ,0x66 ,0x66 ,0x66 ,0x66 ,0x66 ,
[ 2696.851556] 0x66 ,0x66 ,0x66 ,0x66 ,0x66 ,0x66 ,0x66 ,0x66 ,0x66 ,0x66 ,
[ 2696.851564] 0x66 ,0x66 ,0x66 ,0x66 ,0x66 ,0x66 ,0x66 ,0x66 ,0x66 ,0x66 ,
[ 2696.851571] 0x66 ,0x66 ,0x66 ,0x66 ,0x66 ,0x66 ,0x66 ,0x66 ,0x66 ,0x66 ,
[ 2696.851580] BLKDEV:Write-sector:120--size = 4096--
[ 2696.851581] BLKDEV:source, req->buffer:
[ 2696.851583] 0x66 ,0x66 ,0x66 ,0x66 ,0x66 ,0x66 ,0x66 ,0x66 ,0x66 ,0x66 ,
[ 2696.851590] 0x66 ,0x66 ,0x66 ,0x66 ,0x66 ,0x66 ,0x66 ,0x66 ,0x66 ,0x66 ,
[ 2696.851598] 0x66 ,0x66 ,0x66 ,0x66 ,0x66 ,0x66 ,0x66 ,0x66 ,0x66 ,0x66 ,
[ 2696.851605] 0x66 ,0x66 ,0x66 ,0x66 ,0x66 ,0x66 ,0x66 ,0x66 ,0x66 ,0x66 ,
[ 2696.851615] BLKDEV:dest, simp_blkdev_data:
[ 2696.851616] 0x66 ,0x66 ,0x66 ,0x66 ,0x66 ,0x66 ,0x66 ,0x66 ,0x66 ,0x66 ,
[ 2696.851624] 0x66 ,0x66 ,0x66 ,0x66 ,0x66 ,0x66 ,0x66 ,0x66 ,0x66 ,0x66 ,
[ 2696.851632] 0x66 ,0x66 ,0x66 ,0x66 ,0x66 ,0x66 ,0x66 ,0x66 ,0x66 ,0x66 ,
[ 2696.851639] 0x66 ,0x66 ,0x66 ,0x66 ,0x66 ,0x66 ,0x66 ,0x66 ,0x66 ,0x66 ,
[ 2696.851649] 5. SUBMITIO: Call bio->bi_end_io-------------

