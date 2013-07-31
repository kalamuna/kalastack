/**
 *
 * Class that governs the creation of the mysql-server configuration
 *
 */
class mysql::server::config {

  # Dynamically set buffer pool
  $buffer_pool = $::kalamem / 4

  mysql::my { "my.cnf":
    path => "/etc/mysql/my.cnf",
    key_buffer => "${buffer_pool}M",
    innodb_buffer_pool_size => "${buffer_pool}M",
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
