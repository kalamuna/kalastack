/**
 * 
 * Installs and configures the GD extension for PHP5
 * 
 */
class phpfpm::extensions::gd {

  phpfpm::extension { "php5-gd": version => "5.3.10-1ubuntu3.4", }
  
}