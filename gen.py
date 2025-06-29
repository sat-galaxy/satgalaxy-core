vars = [
    "double opt_K",
    "double opt_R",
    "int opt_size_lbd_queue",
    "int opt_size_trail_queue",
    "int opt_first_reduce_db",
    "int opt_inc_reduce_db",
    "int opt_spec_inc_reduce_db",
    "int opt_lb_lbd_frozen_clause",
    "bool opt_chanseok_hack",
    "int opt_chanseok_limit",
    "int opt_lb_size_minimzing_clause",
    "int opt_lb_lbd_minimzing_clause",
    "bool opt_lcm",
    "bool opt_lcm_update_lbd",
    "double opt_var_decay",
    "double opt_max_var_decay",
    "double opt_clause_decay",
    "double opt_random_var_freq",
    "double opt_random_seed",
    "int opt_ccmin_mode",
    "int opt_phase_saving",
    "bool opt_rnd_init_act",
    "double opt_garbage_frac",
    "bool opt_glu_reduction",
    "bool opt_luby_restart",
    "double opt_restart_inc",
    "int opt_luby_restart_factor",
    "int opt_randomize_phase_on_restarts",
    "bool opt_fixed_randomize_phase_on_restarts",
    "bool opt_adapt",
    "bool opt_forceunsat",
    "bool opt_use_asymm",
    "bool opt_use_rcheck",
    "bool opt_use_elim",
    "int opt_grow",
    "int opt_clause_lim",
    "int opt_subsumption_lim",
    "double opt_simp_garbage_frac",
    "int opt_verbosity",
]

for var in vars:
    strs =var.split(" ")
    ty=strs[0]
    name=strs[1]
    # print(f"""void glucose_set_{name}({ty} value);""")

    print(f"""
    void glucose_set_{name}({ty} value) {{
        Glucose::set_{name}(value) ;
    }}""")
