/**
 *
 * Class that governs the creation of the mysql-server configuration
 *
 */
class mysql::server::config {

  mysql::my { "my.cnf":
    path => "/etc/mysql/my.cnf",
    #data_dir => "/etc/kalastack/mysql",
    require => File["/etc/kalastack/mysql"],
    notify => Class["mysql::server::service"],
  }

  file { "/etc/kalastack/mysql":
    ensure  => directory,
    mode    => 777,
    subscribe => File["/etc/kalastack"],
  }

  /*
  user { "mysql":
    groups => ['dialout'],
    require => Class["mysql::server::install"],
  }
  */

}
