[@bs.val] external fetch: string => Js.Promise.t('a) = "fetch";

type state =
  | LoadingTime
  | ErrorFetchingTime
  | LoadedTime(string);

[@react.component]
let make = () => {
  let (state, setState) = React.useState(() => LoadingTime);

    Js.Promise.(
      fetch("http://127.0.0.1:333")
      |> then_(response => response##json())
      |> then_(jsonResponse => {
           setState(_previousState => LoadedTime(jsonResponse##time));
           Js.log(state);
           Js.Promise.resolve();
         })
      |> catch(_err => {
           setState(_previousState => ErrorFetchingTime);
           Js.Promise.resolve();
         })
      |> ignore
    );


  <div
    style={ReactDOMRe.Style.make(
      ~height="120px",
      ~display="flex",
      ~alignItems="center",
      ~justifyContent="center",
      (),
    )}>
    {switch (state) {
                      | ErrorFetchingTime => React.string("An error occurred")
                      | LoadingTime => React.string("Loading...")
                      | LoadedTime(time) => React.string({j|Time: $time|j})
                      }}
  </div>;
};
