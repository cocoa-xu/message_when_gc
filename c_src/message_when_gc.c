#include <erl_nif.h>

ErlNifResourceType * message_resource;

struct message {
    ErlNifEnv *env;
    ErlNifPid pid;
    ERL_NIF_TERM value;
};

static void destruct_message(ErlNifEnv *env, void *obj) {
    printf("destruct_message is called, send value to pid\r\n");
    struct message *m = (struct message *) obj;
    enif_send(NULL, &m->pid, m->env, m->value);
    enif_free_env(m->env);
    printf("destruct_message end\r\n");
}

static ERL_NIF_TERM message_when_gc(ErlNifEnv *env, int argc, const ERL_NIF_TERM argv[]) {
    if (!enif_is_pid(env, argv[0])) {
        return enif_make_badarg(env);
    }
    ErlNifPid pid;
    if (!enif_get_local_pid(env, argv[0], &pid)) {
        return enif_make_tuple2(env, enif_make_atom(env, "error"), enif_make_atom(env, "enif_get_local_pid failed"));
    }

    struct message* m = enif_alloc_resource(message_resource, sizeof(struct message));
    if (!m) {
        return enif_make_tuple2(env, enif_make_atom(env, "error"), enif_make_atom(env, "enif_alloc_resource failed"));
    }

    m->env = enif_alloc_env();
    if (!m->env) {
        return enif_make_tuple2(env, enif_make_atom(env, "error"), enif_make_atom(env, "enif_alloc_env failed"));
    }
    m->pid = pid;
    m->value = enif_make_copy(m->env, argv[1]);
    
    ERL_NIF_TERM term = enif_make_resource_binary(env, m, NULL, 0);
    enif_release_resource(m);
    return term;
}

static int on_load(ErlNifEnv *env, void **_sth1, ERL_NIF_TERM _sth2) {
    ErlNifResourceType *rt = enif_open_resource_type(env, "Elixir.MessageWhenGc.Nif", "message_resource", destruct_message, ERL_NIF_RT_CREATE, NULL);
    if (!rt) return -1;
    message_resource = rt;
    return 0;
}

static int on_reload(ErlNifEnv *_sth0, void **_sth1, ERL_NIF_TERM _sth2) {
    return 0;
}

static int on_upgrade(ErlNifEnv *_sth0, void **_sth1, void **_sth2, ERL_NIF_TERM _sth3) {
    return 0;
}

static ErlNifFunc nif_functions[] = {
    {"message_when_gc", 2, message_when_gc, 0},
};

ERL_NIF_INIT(Elixir.MessageWhenGc.Nif, nif_functions, on_load, on_reload, on_upgrade, NULL);
