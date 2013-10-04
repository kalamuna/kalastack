/**
 *
 * Installs and configures the CURL extension for PHP5
 *
 */
class phpfpm::extensions::curl {

  phpfpm::extension { "php5-curl": version => present, }

  package { "curl":
    ensure => present,
  }

}
