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
}
