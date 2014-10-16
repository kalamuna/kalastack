
/**
 *
 * This will build a basic LEMP stack with some extra goodies for every node that connects
 * to the puppetmaster at kalabox.kalamuna.com
 */

node /^kala\.[a-f0-9]{32}\.box$/  {
  # initialize dependencies
  include kalabox
  include user
  include phpfpm
  include nginx

  # initialize frontend
  include frontend
}
