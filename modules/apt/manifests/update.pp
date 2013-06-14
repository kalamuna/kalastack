/**
 * 
 * runs apt-get update if applicable
 * 
 */
class apt::update {
  
  exec { "apt-update":
      command => "/usr/bin/apt-get update"
  }
  
  Exec["apt-update"] -> Package <| |>
      
}