/**
 * 
 * Installs and configures the GD extension for PHP5
 * 
 */
class phpfpm::extensions::gd {

  phpfpm::extension { "php5-gd": version => present, }
  
}