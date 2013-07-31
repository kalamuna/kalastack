/**
 *
 * Defines and sets default values for a my.cnf file
 *
 */
define mysql::my (

  # basic settings
  $path = "/etc/mysql/my.cnf",
  $port = 3306,
  $socket = "/var/run/mysqld/mysqld.sock",
  $user = "mysql",
  $default_storage_engine = "innodb",

  # fine tuning
  $key_buffer = "384M",
  $max_allowed_packet = "32M",
  $thread_stack = "400K",
  $thread_cache_size = "8",
  $read_rnd_buffer_size = "8M",
  $myisam_sort_buffer_size = "64M",
  $table_open_cache = "512",
  $sort_buffer_size = "2M",
  $read_buffer_size = "2M",

  # query cache config
  $query_cache_limit = "1M",
  $query_cache_size = "64M",

  # innodb
  $innodb_flush_log_at_trx_commit = "0",
  $innodb_buffer_pool_size = "384M",

  # mysqldump
  $msd_max_allowed_packet = "32M",

  # isamchk
  $ikey_buffer_size = "256M",
  $isort_buffer_size = "256M",
  $iread_buffer = "2M",
  $iwrite_buffer = "2M",

  # data location
  $data_dir = "/var/lib/mysql",

) {

  file {
    "${path}":
      path      => "${path}",
      content   => template("mysql/my.cnf.erb"),
  }

}
