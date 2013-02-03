Cryptosign for firmware

* Generate your keypair with key-generate (will ask 3 times for password)
* Put firmware.bin here
* Run key-sign to sign the firmware (will create firmware.sig which has 512 bytes signature prepended)
* Decrypt the signature with key-verify

The signature contains SHA-256 hash followed with a space and original file size, terminated by a newline.
