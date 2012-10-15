/**
 * 
 * Prepend a line to a file if that line doesn't already exist
 * 
 */
define network::prepend ( 
    $file, 
    $line, 
    $refreshonly = 'FALSE',
) {
    
    exec { "/usr/bin/perl -p0i -e 's/^/$line\n/;' '$file'":
        unless      => "/bin/grep -Fxqe '$line' '$file'",
        path        => "/bin",
        refreshonly => $refreshonly,
    }
    
}