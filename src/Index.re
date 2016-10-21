open Lwt;

open Cohttp;

open Cohttp_lwt_unix;

let callback _conn req body => {
  let uri = req |> Request.uri |> Uri.to_string;
  let meth = req |> Request.meth |> Code.string_of_method;
  let headers = req |> Request.headers |> Header.to_string;
  body |> Cohttp_lwt_body.to_string >|= (
    fun body =>
      Printf.sprintf "Uri: %s\nMethod: %s\nHeaders\nHeaders: %s\nBody: %s" uri meth headers body
  ) >>= (
    fun body => Server.respond_string status::`OK body::body ()
  )
};

let server = Server.create mode::(`TCP (`Port 8000)) (Server.make callback::callback ());

ignore (Lwt_main.run server);
