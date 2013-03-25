/**
 * 
 * Installs and configures the mcrypt extension for PHP5
 * 
 */
class phpfpm::extensions::mcrypt  {

  phpfpm::extension { "php5-mcrypt": version => present, }
  
}