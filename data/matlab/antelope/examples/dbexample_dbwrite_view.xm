dbexample_get_demodb_path;

echo on

% Make a named pipe:
pipe_name = ['/tmp/mypipe_' getenv('USER')];

unix( ['mkfifo ' pipe_name] );

% Set a small trap for the upcoming view:
unix( ['cat ' pipe_name ' | dbe - &'] );

db = dbopen( demodb_path,'r' );

dbarrival=dblookup_table( db,'arrival' );
dbwfdisc=dblookup_table( db,'wfdisc' );
db=dbjoin( dbarrival,dbwfdisc );

dbwrite_view( db, pipe_name );

dbclose( db );

echo off
