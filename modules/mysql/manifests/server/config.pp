/**
 *
 * Class that governs the creation of the mysql-server configuration
 *
 */
class mysql::server::config {

  # Dynamically set buffer pool
  # Trick puppet into thinking this is a numer
  $buffer_total_mem = 0 + $::kalamem
  $buffer_pool = $buffer_total_mem / 4

  mysql::my { "my.cnf":
    path => "/etc/mysql/my.cnf",
    key_buffer => "${buffer_pool}M",
    innodb_buffer_pool_size => "${buffer_pool}M",
    #data_dir => "/etc/kalastack/mysql",
    require => File["/etc/kalastack/mysql"],
    notify => Class["mysql::server::service"],
  }

}
