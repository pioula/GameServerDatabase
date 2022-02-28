import React from 'react';
import {fetchTable, fetchTableByObjectName, postObject, removeObject} from "../utils/fetch_utils";
import {Button, Col, FormControl, InputGroup, Row, Stack, Table} from "react-bootstrap";

const table = 'games';

class AddGame extends React.Component {
    emptyGame = {
        name: ''
    }

    constructor(props) {
        super(props);
        this.state = {
            gameName: ''
        };
        this.onChange = this.onChange.bind(this);
        this.onSubmit = this.onSubmit.bind(this);
    }

    onChange(e) {
        this.setState(prevState => ({
            ...prevState,
            gameName: e.target.value
        }));
    }

    async onSubmit(e) {
        e.preventDefault();
        const game = this.emptyGame;
        game.name = this.state.gameName;
        this.setState(prevState => ({
            ...prevState,
            gameName: ''
        }))

        const games = await postObject(table, game);
        this.props.updateGames(games);
    }

    render() {
        return (
            <InputGroup className="mb-3">
                <FormControl
                    placeholder="Input a game name"
                    aria-describedby="basic-addon2"
                    onChange={this.onChange}
                    value={this.state.gameName}
                />
                {
                    this.state.gameName === '' ?
                    <Button variant="success" disabled>
                        Add
                    </Button> :
                    <Button variant="success" onClick={this.onSubmit}>
                        Add
                    </Button>
                }

            </InputGroup>
        );
    }
}

class SearchGame extends React.Component {
    constructor(props) {
        super(props);
        this.state = {
            query: ''
        }

        this.onChange = this.onChange.bind(this);
        this.onSearch = this.onSearch.bind(this);
    }

    onChange(e) {
        this.setState(prevState => ({
            ...prevState,
            query: e.target.value
        }));
    }

    async onSearch(e) {
        e.preventDefault();
        const query = this.state.query;
        this.setState(prevState => ({
            ...prevState,
            query: ''
        }))

        const games = await fetchTableByObjectName('/' + table + '/get-games-by-name', query)
        this.props.updateGames(games);
    }

    render() {
        return (
            <InputGroup className="mb-3">
                <FormControl
                    placeholder="Search game"
                    aria-describedby="basic-addon2"
                    value={this.state.query}
                    onChange={this.onChange}
                />
                <Button variant="primary" onClick={this.onSearch}>
                    Search
                </Button>
            </InputGroup>
        );
    }
}

class GamesTable extends React.Component {
    async onRemove(id) {
        await removeObject(table, id);
        this.props.updateGames([...this.props.games].filter(game => game.id !== id));
    }

    render() {
        const gamesTable = this.props.games.map(game =>
            <tr key={game.id}>
                <td><Button variant={"danger"} size={"sm"} onClick={() => this.onRemove(game.id)}>Remove</Button></td>
                <td>{game.name}</td>
                <td><Button variant={"primary"} size={"sm"} href={`games/leaderboard/${game.id}`}>Leaderboard</Button></td>
                <td><Button variant={"secondary"} size={"sm"} href={`games/records/${game.id}`}>Games</Button></td>
            </tr>);
        return (
            <Table striped>
                <thead>
                    <tr>
                        <th width='7%'/>
                        <th>Game</th>
                        <th width={'7%'}>Leaderboard</th>
                        <th width={'7%'}>Played Games</th>
                    </tr>
                </thead>
                <tbody>
                    {gamesTable}
                </tbody>
            </Table>
        );
    }
}


class Games extends React.Component {
    constructor(props) {
        super(props);
        this.state = {
            games: []
        };
        this.updateGames = this.updateGames.bind(this);
    }

    updateGames(games) {
        this.setState(prevState => ({
            ...prevState,
            games: games
        }));
    }

    async componentDidMount() {
        this.updateGames(await fetchTable(table));
    }

    render() {
        return (
          <>
              <Stack gap={2} className="col-md-10 mx-auto">
                  <Row>
                      <Col>
                          <h2>Games</h2>
                      </Col>
                      <Col>
                          <AddGame updateGames={this.updateGames}/>
                      </Col>
                      <Col>
                          <SearchGame updateGames={this.updateGames} />
                      </Col>
                  </Row>
                  <Row>
                      <Col>
                          <GamesTable updateGames={this.updateGames} games={this.state.games} />
                      </Col>
                  </Row>
              </Stack>
          </>
        );
    }
}

export default Games;