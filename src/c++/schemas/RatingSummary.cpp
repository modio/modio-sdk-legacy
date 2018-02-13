#include "c++/schemas/RatingSummary.h"

namespace modio
{
  void RatingSummary::initialize(ModioRatingSummary modio_ratings)
  {
    this->total_ratings = modio_ratings.total_ratings;
    this->positive_ratings = modio_ratings.positive_ratings;
    this->negative_ratings = modio_ratings.negative_ratings;
    this->percentage_positive = modio_ratings.percentage_positive;
    this->weighted_aggregate = modio_ratings.weighted_aggregate;
    if(modio_ratings.display_text)
      this->display_text = modio_ratings.display_text;
  }

  json RatingSummary::toJson()
  {
    json rating_summary_json;

    rating_summary_json["total_ratings"] = this->total_ratings;
    rating_summary_json["positive_ratings"] = this->positive_ratings;
    rating_summary_json["negative_ratings"] = this->negative_ratings;
    rating_summary_json["percentage_positive"] = this->percentage_positive;
    rating_summary_json["weighted_aggregate"] = this->weighted_aggregate;
    rating_summary_json["display_text"] = this->display_text;

    return rating_summary_json;
  }
}
