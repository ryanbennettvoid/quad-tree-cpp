
const Log = require( 'log' ), log = new Log();
const Promise = require( 'bluebird' );
const net = require( 'net' );
const helpers = require( './helpers.js' );

const DEFAULT_OPTIONS = {
  host: '127.0.0.1',
  port: 7889,
  debug: false
};

const Client = ( options ) => {

  const _options = Object.assign( {}, DEFAULT_OPTIONS, options );
  const { host, port, debug } = _options;

  return {

    evoke: ( functionName, args ) => {

      if ( debug ) log.debug( `sending request: ${functionName} -> ${JSON.stringify( args )}` );

      return new Promise( ( resolve, reject ) => {

        const c = net.Socket();

        c.connect( port, host );

        c.write( JSON.stringify( { functionName, args } ) );

        let fullResponse = '';

        c.on( 'data', ( data ) => {
          if ( !data || data.length === 0 ) return c.end();
          fullResponse += data;
        } );

        c.on( 'close', () => {
          const message = helpers.parseSocketResponse( fullResponse );
          const { timestamp_fn_start, timestamp_fn_end, err, results } = message;
          if ( debug ) log.debug( `request resolved: ${functionName} -> ${timestamp_fn_end-timestamp_fn_start}ms` );
          resolve( message );
        } );

        c.on( 'error', ( err ) => {
          c.end();
          reject( err );
        } );

      } );

    }

  };

};

module.exports = Client;