#include "data_containers/Ratings.h"

namespace modworks
{
  Ratings::Ratings(json ratings_json)
  {
    this->total = -1;
    if(hasKey(ratings_json, "total"))
      this->total = ratings_json["total"];

    this->positive = -1;
    if(hasKey(ratings_json, "positive"))
      this->positive = ratings_json["positive"];

    this->negative = -1;
    if(hasKey(ratings_json, "negative"))
      this->negative = ratings_json["negative"];

    this->weighted = -1;
    if(hasKey(ratings_json, "weighted"))
      this->weighted = ratings_json["weighted"];

    this->percentage = -1;
    if(hasKey(ratings_json, "percentage"))
      this->percentage = ratings_json["percentage"];

    this->stars = -1;
    if(hasKey(ratings_json, "stars"))
      this->stars = ratings_json["stars"];

    this->text = "";
    if(hasKey(ratings_json, "text"))
      this->text = ratings_json["text"];
  }
}
