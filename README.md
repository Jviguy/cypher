# cypher
A simple yet seeming irreversible string encoding algorithm 

## Information
cypher uses unix time stamps as "seeds" for the encoding of values. Meaning to decode the timestamp / the message you would either need the one of the characters or the timestamp.<br>
That doesn't seem all that secure especially stating with account creation dates and such and so to make up for this we add a third variable into the equation the salt.<br>
The salt is a interger that is multiplied onto the encoded character (the encoded character is the character's ascii value + the timestamp). This makes it so that too find the value of the timestamp or the characters. <br>
You would have to get the salt which can be a completely random integer.

## The Math
So theres a lot of math that goes on behind this even without using any bitwise operations atm the current semantics go like.<br>
### Encoding
```cpp
//No salt
encodedchar = char + timestamp
//With salt
encodedchar = salt*(char + timestamp)
```
### Decoding
```cpp
//No salt
decodedchar = encodedchar - timestamp
//With salt
decodedchar = encodedchar/salt - timestamp
```
## Usage

### Building
This project is made with cmake meaning that the simplest way to build it is.<br>
```bash
mdkir build
cd build
cmake ../
make all
```
### Switches

#### Hex (-h)
Turns input for decoding and output for encoding into a hex form<br>
```bash
cypher -h -e bruh
```

#### Timestamp (-t)
Used for decoding and encoding
##### Decoding
Used as a timestamp to subtract from the encoded character
```bash
cypher -t 200 -d 269 269 269
```
##### Encoding
Used as the cts rather than the current time
```bash
cypher -t 200 -e EEE
```
#### Salting (-s)
Sets a salt value for encoding and decoding
```bash
cypher -s 2 -e bruh
```
#### Encoding (-e)
Starts the encoding trail so that every argument after the switch is encoded
```bash
cypher -e hey guys im cool
```
#### Decoding (-d)
Starts the decoding trail so that every argument after the switch is treated as a long and is decoded with the timestamp
```bash
cypher -t 200 -d 269 277 267
```
