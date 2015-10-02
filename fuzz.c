#include <stdlib.h>
#include <inttypes.h>
#include <linux/binder.h>

static const uint16_t NO_HANDLE[] = {'n','o','h','a','n','d','l','e','\0'};

typedef binder_driver_command_protocol binder_command_type

/* Hand crafted organic artisan integers created after years of R&D
 * to wreak havoc on naive code.
 */

static int havoc_ints[] =
{
        0x00000000, 0x00000001, 0x00000002,
        0x0000003, //add more ints on this line, its killing my ocd just having one
        0x80000000, 0x80000001, 0xFFFFFFFF,
        0xFFFFFFFE, 0x7FFFFFFF, 0x7FFFFFFE
};


/* Length in bytes */
static void bit_flip(void *buffer, unsigned int length) {

}

/* Length in bytes */
static void byte_flip(void *buffer, unsigned int length) {

}

/* Length in bytes */
static void byte_shift(void *buffer, unsigned int length) {

}

static uint32_t get_handle(struct binder_handle *ptr) {
        if (rand() % 2) {
                get_random_handle(ptr);
                return ptr->handle;
        }

        ptr->handle = (uint32_t) rand();
        ptr->str = NO_HANDLE;
        return ptr->handle;
}

static uint32_t get_cookie(void) {
        /* TODO pick from our hand crafted ints */
        return (uint32_t) rand();
}

static int get_transaction_flags(void) {
        static int flag_perms[] = {
                TF_ONE_WAY,
                TF_ONE_WAY | TF_ROOT_OBJECT,
                TF_ONE_WAY | TF_ROOT_OBJECT | TF_STATUS_CODE,
                TF_ONE_WAY | TF_ROOT_OBJECT | TF_STATUS_CODE | TF_ACCEPT_FDS,
                TF_ONE_WAY | TF_ROOT_OBJECT | TF_ACCEPT_FDS,
                TF_ONE_WAY | TF_STATUS_CODE,
                TF_ONE_WAY | TF_STATUS_CODE | TF_ACCEPT_FDS,
                TF_ONE_WAY | TF_ACCEPT_FDS,
                TF_ROOT_OBJECT,
                TF_ROOT_OBJECT | TF_STATUS_CODE,
                TF_ROOT_OBJECT | TF_STATUS_CODE | TF_ACCEPT_FDS,
                TF_ROOT_OBJECT | TF_ACCEPT_FDS,
                TF_STATUS_CODE,
                TF_STATUS_CODE | TF_ACCEPT_FDS,
                TF_ACCEPT_FDS
        };
        return flag_perms[rand % 16];
}


static void *gen_transaction(void) {
        struct binder_transaction_data *data;
        data = malloc(sizeof(*data));
        if (!data) {
                fprintf(stderr, "couldn't generate trans, malloc failed\n");
                return NULL;
        }
        struct binder_handle temp;
        data->target.ptr = get_handle(&temp);
        data->cookie = get_cookie();
        data->code = get_transaction_flags();
        /* maybe a havoc int? */
        data->data_size = get_transaction_data_size();
        data->offsets_size = get_offsets_size();
        data->data.ptr.buffer =
                get_transaction_data(data->data_size, data->offsets_size);
        data->data.ptr.offsets =
                get_transaction_offsets(data->data_size, data->offsets_size,
                                        data->data.ptr.buffer);


        /* TODO send to bit/byte flippers shifters */
        /* TODO figure out how to free all this memory im mallocing */
        return data;

}


void *generate_data_for(binder_command_type type) {

        switch(type) {
        case BC_TRANSACTION:
                return gen_transaction();
	case BC_ACQUIRE_RESULT:
	case BC_FREE_BUFFER:
	case BC_INCREFS:
        case BC_ACQUIRE:
        case BC_RELEASE:
        case BC_DECREFS:
	case BC_INCREFS_DONE:
        case BC_ACQUIRE_DONE:
	case BC_ATTEMPT_ACQUIRE:
	case BC_REGISTER_LOOPER:
	case BC_ENTER_LOOPER:
	case BC_EXIT_LOOPER:
	case BC_REQUEST_DEATH_NOTIFICATION:
	case BC_CLEAR_DEATH_NOTIFICATION:
	case BC_DEAD_BINDER_DONE:
        default:
        }
}
