#ifndef ANOMALY_DETECTOR_H_
#define ANOMALY_DETECTOR_H_

struct AnomalyDetecionConfig
{
    unsigned int season_length;
    double alpha;
    double beta;
    double gamma;
    unsigned int n_preds;
};

class AnomalyDetection
{
public:
    AnomalyDetection(const AnomalyDetecionConfig& config);
    ~AnomalyDetection();
};

#endif