#ifndef DMAO_ALLOCATOR_PARAMS_HPP
#define DMAO_ALLOCATOR_PARAMS_HPP

namespace dmao {

struct allocator_strategy {
    double predict_demand_alpha;
    double predict_demand_beta;
};

struct allocator_args {
    double utilization_weight;
    double respone_time_weight;
    double stability_weight;
};

} // namespace dmao

#endif
