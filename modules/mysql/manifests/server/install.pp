/**
 *
 * Sets up mysql-server by:
 *
 * 1. Installs the mysql-server package
 * 2. Installs the php5 mysql extension
 * 3. Adds the mysql root user and sets it's password
 *
 */
class mysql::server::install {

  $password = "password"

  # Install mysql-server
  package { "mysql-server":
  	ensure => present
  }

  # Install php5 extension
  phpfpm::extension { "php5-mysql": version => present, }

  # Add the root user
  exec { "Set MySQL server root password":
    subscribe => Package["mysql-server"],
    refreshonly => true,
    unless => "mysqladmin -uroot -p${password} status",
    path => "/bin:/usr/bin",
    command => "mysqladmin -uroot password ${password}",
  }

}
