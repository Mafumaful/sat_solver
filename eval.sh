#!/bin/bash
./build/bonus <test/test0.in >test/test0_your.out # output your answer
diff test/test0.out test/test0_your.out

./build/bonus <test/test1.in >test/test1_your.out # output your answer
diff test/test1.out test/test1_your.out

