import React from 'react';
import {Button, Col, Container, Dropdown, Form, Modal, Row, Stack, Table, Spinner} from "react-bootstrap";
import {checkPathId, Interval, SingleInput, updateFromInterval, updateFromSingleInput} from "../utils/class_utils";
import {fetchObject, GET, getQueryPath} from "../utils/fetch_utils";

const rankingsURI = 'rankings/list';
const leaderboardsURI = 'leaderboards';

class SearchPlayer extends React.Component {
    emptyQuery = {
        minPosition: 0,
        maxPosition: 0,
        nick: '',
        minRanking: 0,
        maxRanking: 0,
        minTotal: 0,
        maxTotal: 0,
        minWins: 0,
        maxWins: 0,
        minLoses: 0,
        maxLoses: 0
    }

    constructor(props) {
        super(props);
        this.state = {
            query: this.emptyQuery,
            show: false
        }

        this.updateFromChildInterval = this.updateFromChildInterval.bind(this);
        this.updateFromChildSingleInput = this.updateFromChildSingleInput.bind(this);
        this.handleShow = this.handleShow.bind(this);
        this.handleClose = this.handleClose.bind(this);
        this.handleSubmit = this.handleSubmit.bind(this);
    }

    updateFromChildInterval(interval, minValueName, maxValueName) {
        this.setState(prevState => ({
            ...prevState,
            query: updateFromInterval(this.state.query, interval, minValueName, maxValueName)
        }));
    }

    updateFromChildSingleInput(singleInput, valueName) {
        this.setState(prevState => ({
            ...prevState,
            query: updateFromSingleInput(this.state.query, singleInput, valueName)
        }));
    }

    handleClose() {
        this.setState({
            query: this.emptyQuery,
            show: false
        });
    }

    handleShow() {
        this.setState({
            query: this.emptyQuery,
            show: true
        });
    }

    async handleSubmit(e) {
        e.preventDefault();

        let query = getQueryPath(this.state.query);
        query = '&' + query.substring(1);
        const response = await fetch('/' + leaderboardsURI + '/query' +
                                            '?game=' + this.props.gameId +
                                            '&ranking=' + this.props.rankingId +
                                            query, GET)

        this.props.updateLeaderboard(await response.json());
        this.handleClose();
    }

    render() {
        return (
            <>
                <Button variant={"primary"} onClick={this.handleShow}>
                    Search
                </Button>

                <Modal size={"lg"} show={this.state.show} onHide={this.handleClose}>
                    <Modal.Header closeButton>
                        <Modal.Title>Search</Modal.Title>
                    </Modal.Header>
                    <Form onSubmit={this.handleSubmit}>
                        <Modal.Body>
                            <Interval
                                updateParent={this.updateFromChildInterval}
                                name={'Position'}/>
                            <SingleInput
                                updateParent={this.updateFromChildSingleInput}
                                valueName={'nick'}
                                valueTitle={'Nickname'}/>
                            <Interval
                                updateParent={this.updateFromChildInterval}
                                name={'Ranking'}
                                min={-1000000}/>
                            <Interval
                                updateParent={this.updateFromChildInterval}
                                name={'Total'}/>
                            <Interval
                                updateParent={this.updateFromChildInterval}
                                name={'Wins'}/>
                            <Interval
                                updateParent={this.updateFromChildInterval}
                                name={'Draws'}/>
                        </Modal.Body>
                        <Modal.Footer>
                            <Button variant={"secondary"} onClick={this.handleClose}>
                                Close
                            </Button>
                            <Button variant={"primary"} type={"submit"}>
                                Search
                            </Button>
                        </Modal.Footer>
                    </Form>
                </Modal>
            </>
        )
    }
}

class RankingDropdown extends React.Component {
    constructor(props) {
        super(props);
        let ranking = props.rankings.filter(ranking =>
        ranking.id === props.rankingId);
        this.state = {
            rankingName: ranking[0].name,
            rankingId:ranking[0].id
        }

        this.handleChange = this.handleChange.bind(this);
    }

    async handleChange(id) {
        await this.props.updateLeaderboard(id);
    }

    render() {
        const rankings = this.props.rankings.map(ranking =>
            <Dropdown.Item
                key={ranking.id}
                onClick={(e) => this.handleChange(ranking.id, e)}>
                    {ranking.name}
            </Dropdown.Item>
        );
        return (
            <Dropdown>
                <Dropdown.Toggle variant={"link"} id={"dropdown-basic"} >
                    {this.state.rankingName}
                </Dropdown.Toggle>
                <Dropdown.Menu>
                    {rankings}
                </Dropdown.Menu>
            </Dropdown>
        );
    }
}

class LeaderboardTable extends React.Component {
    render() {
        const leaderboardTable = this.props.leaderboard.map(row =>
        <tr key={row.nick}>
            <td>{row.position}</td>
            <td>{row.nick}</td>
            <td>{row.ranking}</td>
            <td>{row.total}</td>
            <td>{row.wins}</td>
            <td>{row.draws}</td>
        </tr>);
        return (
            <Table striped>
                <thead>
                    <tr>
                        <th width='7%'>#</th>
                        <th>Nick</th>
                        <th>
                            <RankingDropdown
                                rankings={this.props.rankings}
                                updateLeaderboard={this.props.updateLeaderboard}
                                rankingId={this.props.rankingId}
                            />
                        </th>
                        <th>Played Games</th>
                        <th>Wins</th>
                        <th>Draws</th>
                    </tr>
                </thead>
                <tbody>
                    {leaderboardTable}
                </tbody>
            </Table>
        );
    }
}

class Leaderboard extends React.Component {
    constructor(props) {
        super(props);
        this.state = {
            gameId: 0,
            rankingId: 0,
            isCorrect: true, //is path correct
            isLoaded: false,
            leaderboard: [],
            rankings: [],
            gameName: ''
        }
        this.updateLeaderboard = this.updateLeaderboard.bind(this);
        this.updateLeaderboardWithRanking = this.updateLeaderboardWithRanking.bind(this);
    }

    updateLeaderboard(leaderboard) {
        this.setState(prevState => ({
            ...prevState,
            leaderboard: leaderboard
        }));
    }

    async updateLeaderboardWithRanking(id) {
        this.setState(prevState => ({
            ...prevState,
            isLoaded: false,
            rankingId: id
        }));
        const leaderboard = await this.getLeaderboard(id);
        this.setState(prevState => ({
            ...prevState,
            leaderboard: leaderboard,
            isLoaded: true
        }));
    }

    async getRankings() {
        const response = await fetch('/' + rankingsURI, GET);
        return await response.json();
    }

    async getLeaderboard(id) {
        const response = await fetch('/' + leaderboardsURI + '/list?game=' +
                                        this.state.gameId + '&ranking=' + id, GET);
        return await response.json();
    }

    async componentDidMount() {
        const match = checkPathId(window.location.pathname,
                            'games/leaderboard/:id');

        if (!match.isCorrect) {
            this.setState(prevState => ({
                ...prevState,
                isCorrect: false
            }));
            return;
        }
        else {
            this.setState(prevState => ({
                ...prevState,
                isCorrect: true,
                gameId: match.id
            }));
        }

        const game = await fetchObject('games', Number(match.id));
        const rankings = await this.getRankings();
        this.setState(prevState => ({
            ...prevState,
            rankings: rankings,
            gameName: game.name
        }));
        await this.updateLeaderboardWithRanking(this.state.rankings[0].id);
    }

    render() {
        return (
            <>
                {!this.state.isCorrect ?
                    <Container>
                        <Row>
                            <Col>
                                <h1>Error: Game Not Found!</h1>
                            </Col>
                        </Row>
                    </Container> :
                    this.state.isLoaded ?
                    <Stack gap={2} className={"col-md-10 mx-auto"}>
                        <Row>
                            <Col>
                                <h2>{this.state.gameName} leaderboard</h2>
                            </Col>
                            <Col md={"auto"}>
                                <SearchPlayer
                                    gameId={this.state.gameId}
                                    rankingId={this.state.rankingId}
                                    updateLeaderboard={this.updateLeaderboard}/>
                            </Col>
                        </Row>
                        <Row>
                            <Col>
                                <LeaderboardTable
                                    leaderboard={this.state.leaderboard}
                                    rankings={this.state.rankings}
                                    rankingId={this.state.rankingId}
                                    updateLeaderboard={this.updateLeaderboardWithRanking}/>
                            </Col>
                        </Row>
                    </Stack> :
                    <Stack gap={2} className={"col-md-10 mx-auto"}>
                        <Row>
                            <Col align={"center"}>
                                <Spinner animation={"border"} />
                            </Col>
                        </Row>
                    </Stack>
                }
            </>
        );
    }
}

export default Leaderboard;