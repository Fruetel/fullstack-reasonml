let src = Logs.Src.create("http", ~doc="HTTP server");
module Log = (val (Logs.src_log(src): (module Logs.LOG)));

module Dispatch = (Clock: Mirage_clock.PCLOCK, Server: Cohttp_lwt.S.Server) => {
  let serve = clock => {
    let callback = ((_, cid), request, _body) => {
      let uri = request
        |> Cohttp.Request.uri
        |> Uri.to_string;

      Log.info(f => f("Request URI: %s", uri));

      let time = Clock.now_d_ps(clock) |> Ptime.v;
      Log.info(f => f("responding to %s", Cohttp.Connection.to_string(cid)));

      let addHeader = (name, value, headers) =>
        Cohttp.Header.add(headers, name, value);

      let responseHeaders = () =>
        Cohttp.Header.init_with("Content-Type", "application/json")
          |> addHeader("access-control-allow-origin", "*");

      let body = Format.asprintf("{ \"time\": \"%a\" }", Ptime.pp_human(), time);

      Server.respond_string(~status=`OK, ~headers=responseHeaders(), ~body, ());
    };
    Server.make(~callback, ());
  };
};

module HTTP = (Clock: Mirage_clock.PCLOCK, Server: Cohttp_lwt.S.Server) => {
  let start = (clock, http) => {
    let rec port = Key_gen.port()
    and tcp = `TCP(port);
    Log.info(f => f("listening on %d/TCP", port));
    module D = Dispatch(Clock, Server);
    http(tcp) @@ D.serve(clock);
  };
};
