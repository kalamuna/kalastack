/**
 * 
 * Definition for building a php.ini file
 * 
 */
define php5::ini (
    
  $path = "/etc/php.ini",
  $disable_functions = "pcntl_alarm,pcntl_fork,pcntl_waitpid,pcntl_wait,pcntl_wifexited,pcntl_wifstopped,pcntl_wifsignaled,pcntl_wexitstatus,pcntl_wtermsig,pcntl_wstopsig,pcntl_signal,pcntl_signal_dispatch,pcntl_get_last_error,pcntl_strerror,pcntl_sigprocmask,pcntl_sigwaitinfo,pcntl_sigtimedwait,pcntl_exec,pcntl_getpriority,pcntl_setpriority,",
  $max_execution_time = 30,
  $max_input_time = 60,
  $memory_limit = "512M",
  $error_reporting = "E_ALL | E_STRICT",
  $display_errors = "On",
  $track_errors = "On",
  $html_errors = "On",
  $error_log = "/var/log/php_errors.l#og",
  $post_max_size = "200M",
  $upload_max_filesize = "200M",
  
) {
	
  file {
    "${path}":
      path      => "${path}",
      content   => template("php5/php.ini.erb"),
  }
  
}