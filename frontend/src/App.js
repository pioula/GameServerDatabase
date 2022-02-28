import React from 'react';
import Main from './pages/Main'
import Navbar from 'react-bootstrap/Navbar'
import {Container} from "react-bootstrap";
import Stack from "react-bootstrap/Stack";
import Games from "./pages/Games";
import Players from "./pages/Players";
import Ranks from "./pages/Ranks";
import {Route, Switch} from "react-router-dom";
import Leaderboard from "./pages/Leaderboard";
import {Records} from "./pages/Records";

function App() {
  return (
      <>
          <Stack gap={5}>
              <Navbar bg="dark" expand="lg" variant="dark">
                  <Container>
                      <Navbar.Brand href='/'>Game Server</Navbar.Brand>
                  </Container>
              </Navbar>
              <Switch>
                  <Route exact path='/' component={Main}/>
                  <Route exact path='/players' component={Players}/>
                  <Route exact path='/games' component={Games}/>
                  <Route exact path='/ranks' component={Ranks}/>
                  <Route path='/games/leaderboard' component={Leaderboard}/>
                  <Route path='/games/records' component={Records}/>
              </Switch>
          </Stack>
      </>
);
}

export default App;
