#ifndef ANOMALY_DETECTOR_H_
#define ANOMALY_DETECTOR_H_

struct AnomalyDetecionConfig
{
    unsigned int season_length;
    unsigned int n_preds;
    double alpha;
    double beta;
    double gamma;
};

class AnomalyDetection
{
public:
    AnomalyDetection(const AnomalyDetecionConfig& config);
    ~AnomalyDetection();
};

#endif