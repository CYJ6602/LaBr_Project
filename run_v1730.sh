#! /bin/bash

for i in {0..100}
do 
    ./V1730_DPP_PSD<<EOF
    16367
    1800
    LaBr_152Eu_PRD_$i.root
EOF
done
