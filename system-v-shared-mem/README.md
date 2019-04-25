# system-v-shared-memory

    $ gcc svshm_xfr_writer.c -o writer_svshm_xfr.out  ../lib/error_functions.c ../svsem/binary_sems.c
    $ gcc svshm_xfr_reader.c -o reader_svshm_xfr.out  ../lib/error_functions.c ../svsem/binary_sems.c
    $ ./writer_svshm_xfr.out < /etc/services &
    [...] 27437
    $ ./reader_svshm_xfr.out > out.txt
    Received 95915 bytes (95 xfrs)

Done :) !