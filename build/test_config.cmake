set(MT_SCHEDULER_CFLAGS
    "-DNBP_MT_SCHEDULER\
    -DNBP_MT_SCHEDULER_NUMBER_OF_THREADS=4"
)

set(MT_SCHEDULER_LFLAGS
    "-lpthread -pthread"
)

list(APPEND TESTS
    tmp1 "" ""
    tmp2 ${MT_SCHEDULER_CFLAGS} ${MT_SCHEDULER_LFLAGS}
    check_build_configuration "" ""
    check_leak_sanitizer "" ""
    check_thread_sanitizer "" "-lpthread -pthread"
)
