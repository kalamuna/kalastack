/**
 * 
 * Execute apt-get update first
 * 
 */
class update::install {

exec { "apt-update":
    command => "/usr/bin/apt-get update"
}

Exec["apt-update"] -> Package <| |>
  
}
