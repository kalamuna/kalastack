/**
 * 
 * Installs drush
 * 
 */
class drush::sqlsync {
  
  package { "pv":
    ensure   => present,
    require => Class["drush::install"],
  }
  
  exec { "installsqlsyncpipe":
    path    => "/bin:/usr/bin",
    unless  => "drush | grep sql-sync-pipe",
    command => "sudo drush dl drush_sql_sync_pipe --destination=/usr/share/drush/commands/kala && sudo drush cache-clear drush",
    require => Class["drush::install"],
  }
     
}