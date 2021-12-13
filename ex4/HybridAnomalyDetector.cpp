
#include "HybridAnomalyDetector.h"



HybridAnomalyDetector::HybridAnomalyDetector() {
}

HybridAnomalyDetector::~HybridAnomalyDetector() {
	// TODO Auto-generated destructor stub
}

void HybridAnomalyDetector::HybridLearnNormal(const TimeSeries& ts) {
  learnNormal(ts);
  for (long int i = 0; i < this->cf.size(); i++) {
    if (cf.at(i).threshold/1.1 < 0.9) {
      cf.at(i).circle =
       findMinCircle(floatsToPoints(ts.getColumnByName(cf.at(i).feature1),
       ts.getColumnByName(cf.at(i).feature2)),
        ts.getColumnByName(cf.at(i).feature1).size());
    }
    else {
      cf.at(i).circle = NULL;
    }
  }

  }

  vector<AnomalyReport> HybridAnomalyDetector::detect(const TimeSeries& ts){
    std::vector<AnomalyReport> report = {};
    for (int i = 0; i < this->cf.size(); i++) {
      std::vector<float> column1 = ts.getColumnByName(this->cf.at(i).feature1);
      std::vector<float> column2 = ts.getColumnByName(this->cf.at(i).feature2);
      TimeSeries newTS = TimeSeries(column1, this->cf.at(i).feature1,column2, this->cf.at(i).feature2);
      if(cf.at(i).circle == NULL) {
        std::vector<AnomalyReport> v = SimpleAnomalyDetector::detect(newTS);
        report.insert(report.end(), v.begin(), v.end());
      }
      else {
        std::vector<AnomalyReport> v = {};
        for (int j = 0; j < column1.size() ; j++) {
          if(minCircle::isInsideCircle(cf.at(i).circle, column1.at(j), column2.at(j)) == 0) {
            report.push_back(AnomalyReport(string(cf.at(i).feature1 + "-" + cf.at(i).feature2), j+1));
          }
        }
      }

    }
   }

Point ** HybridAnomalyDetector::floatsToPoints(std::vector<float> x, std::vector<float> y) {
  Point ** result;
  for (int i = 0; i < x.size() ; i++) {
      Point p(x.at(i), y.at(i));
      result[i] = &p;
  }
  return result;
}
