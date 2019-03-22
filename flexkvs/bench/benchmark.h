#include <stdbool.h>

#include "rng.h"


enum key_dist {
    DIST_UNIFORM,
    DIST_ZIPF,
};

struct settings {
    uint32_t dstip;
    uint16_t dstport;
    uint16_t threads;
    uint16_t conns;
    uint16_t pending;

    uint32_t keynum;
    union {
        struct {
            double s;
        } zipf;
    } keydistparams;
    double get_prob;
    enum key_dist keydist;
    uint64_t key_seed;
    uint64_t op_seed;
    uint32_t request_gap;
    uint32_t warmup_time;
    uint32_t cooldown_time;
    uint32_t run_time;
    uint16_t keysize;
    uint16_t valuesize;

    uint8_t batchsize;

    bool keybased;
};

struct key {
    void *key;
    size_t keylen;
    double cdf;
};

struct workload {
    struct rng op_rng;
    struct key *keys;
    size_t keys_num;
};

struct workload_core {
    struct rng rng;
};

enum workload_op {
    WL_OP_GET,
    WL_OP_SET,
};

extern struct settings settings;

enum error_ids {
    ERR_SUCCESS,
    ERR_KEY_ENOENT,
    ERR_KEY_EEXIST,
    ERR_E2BIG,
    ERR_EINVAL,
    ERR_NOT_STORED,
    ERR_DELTA_BADVAL,
    ERR_UNKNOWN_CMD,
    ERR_ENOMEM,
    ERR_OTHER,
    ERR_MAX,
};

void print_usage(void);
void init_settings(struct settings *s);
int parse_settings(int argc, char *argv[], struct settings *s);

bool trace_open(const char *path);
bool trace_init(void);
void trace_request_get(uint8_t thread, struct key *key, uint16_t id);
void trace_request_set(uint8_t thread, struct key *key, uint32_t valsz,
        uint16_t id);
void trace_response(uint8_t thread, uint16_t id, uint8_t err);
void trace_flush(uint8_t thread);

void workload_init(struct workload *wl);
void workload_core_init(struct workload *wl, struct workload_core *wc);
void workload_op(struct workload *wl, struct workload_core *wc, struct key **k,
        enum workload_op *op);
