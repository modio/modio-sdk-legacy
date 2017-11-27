#include "instance_data_containers/Ratings.h"

namespace modio
{
  void Ratings::initialize(ModioRatings modio_ratings)
  {
    this->total = modio_ratings.total;
    this->positive = modio_ratings.positive;
    this->negative = modio_ratings.negative;
    this->percentage = modio_ratings.percentage;
    this->weighted = modio_ratings.weighted;
    this->text = modio_ratings.text;
  }
}
