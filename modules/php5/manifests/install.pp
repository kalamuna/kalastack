/**
 *
 * Installs PHP5 for CLI
 *
 */
class php5::install {

  package { "python-software-properties":
    ensure => present,
    require => Exec['php54 apt update']
  }

  exec { "add php54 apt-repo":
    command => '/usr/bin/add-apt-repository ppa:ondrej/php5-oldstable -y',
    require => Package['python-software-properties'],
  }

  exec { "php54 apt update":
    command => '/usr/bin/apt-get update',
  }

  package { "php5-cli":
    ensure => present,
  }

}
