set(MT_SCHEDULER_CFLAGS
    "-DNBP_MT_SCHEDULER\
    -DNBP_MT_SCHEDULER_NUMBER_OF_THREADS=4"
)

set(MT_SCHEDULER_LFLAGS
    "-lpthread -pthread"
)

list(APPEND TESTS
    check_build_configuration "" ""
    check_leak_sanitizer "" ""
    check_thread_sanitizer "" "-lpthread -pthread"
    check_ub_sanitizer "" ""
    check_address_sanitizer_heap_use_after_free "" ""
    check_address_sanitizer_heap_buffer_overflow "" ""
    check_address_sanitizer_stack_buffer_overflow "" ""
    check_address_sanitizer_global_buffer_overflow "" ""
    check_address_sanitizer_stack_use_after_return "" ""
    check_address_sanitizer_pointer_comparison "" ""
    check_address_sanitizer_pointer_subtraction "" ""
)
