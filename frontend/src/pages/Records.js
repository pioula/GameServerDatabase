import React from'react';
import {fetchObject, GET, getQueryPath, POST} from "../utils/fetch_utils";
import {checkPathId, Interval, SingleInput, updateFromInterval, updateFromSingleInput} from "../utils/class_utils";
import {Col, Container, Row, Stack, Table, Spinner, Button, Modal, Form} from "react-bootstrap";

const recordsURI = 'records'

class AddRecord extends React.Component {
    resetStateQuery() {
        this.setState(prevState => ({
            ...prevState,
            query: {
                moves: '',
                nickOne: '',
                nickTwo: '',
                winner: 0
            }
        }));
    }

    constructor(props) {
        super(props);
        this.state = {
            query: {
                moves: '',
                nickOne: '',
                nickTwo: '',
                winner: 0
            },
            show: false,
            validated: false
        }

        this.updateFromChildSingleInput = this.updateFromChildSingleInput.bind(this);
        this.handleClose = this.handleClose.bind(this);
        this.handleSubmit = this.handleSubmit.bind(this);
        this.handleShow = this.handleShow.bind(this);
        this.resetStateQuery = this.resetStateQuery.bind(this);
        this.handleResultChange = this.handleResultChange.bind(this);
        this.handleMoves = this.handleMoves.bind(this);
    }

    updateFromChildSingleInput(singleInput, valueName) {
        this.setState(prevState => ({
            ...prevState,
            query: updateFromSingleInput(this.state.query, singleInput, valueName)
        }));
    }

    handleClose() {
        this.setState(prevState => ({
            ...prevState,
            show: false
        }));
        this.resetStateQuery();
    }

    handleShow() {
        this.setState(prevState => ({
            ...prevState,
            show: true,
            validated: false
        }));
        this.resetStateQuery();
    }

    handleResultChange(winner) {
        this.state.query.winner = winner;
    }

    handleMoves(e) {
       this.state.query.moves = e.target.value;
    }

    async handleSubmit(e) {
        e.preventDefault();
        const form = e.currentTarget;
        if (form.checkValidity() === false) {
            e.stopPropagation();
            this.setState(prevState => ({
                ...prevState,
                validated: true
            }));
        } else {
            let playerOne = await fetchObject('players', this.state.query.nickOne);
            let playerTwo = await fetchObject('players', this.state.query.nickTwo);
            if (playerOne.age < 0 || playerTwo.age < 0) {
                console.log("error!");
                this.handleClose();
                return;
            }
            const newRecord = {
                date: new Date(),
                moves: this.state.query.moves,
                nickOne: this.state.query.nickOne,
                nickTwo: this.state.query.nickTwo,
                winner: this.state.query.winner
            }

            this.props.addRecord(newRecord);
            this.handleClose();
        }
    }

    render() {
        return (
          <>
              <Button variant={"success"} onClick={this.handleShow}>
                  Add game
              </Button>
              <Modal size={"lg"} show={this.state.show} onHide={this.handleClose}>
                  <Modal.Header closeButton>
                      <Modal.Title>Add Game</Modal.Title>
                  </Modal.Header>
                  <Form noValidate validated={this.state.validated} onSubmit={this.handleSubmit}>
                      <Modal.Body>
                          <SingleInput
                              updateParent={this.updateFromChildSingleInput}
                              valueName={'nickOne'}
                              valueTitle={'Player One'}
                              required={true}/>
                          <SingleInput
                              updateParent={this.updateFromChildSingleInput}
                              valueName={'nickTwo'}
                              valueTitle={'Player Two'}
                              required={true}/>
                          <Form.Check
                              label={"1–0"}
                              type={"radio"}
                              name={"group1"}
                              inline
                              onClick={() => this.handleResultChange(1)}
                          />
                          <Form.Check
                              label={"½–½"}
                              name={"group1"}
                              type={"radio"}
                              inline
                              defaultChecked={true}
                              onClick={() => this.handleResultChange(0)}
                          />
                          <Form.Check
                              label={"0–1"}
                              name={"group1"}
                              type={"radio"}
                              inline
                              onClick={() => this.handleResultChange(2)}
                          />
                          <Form.Group className="mb-3">
                              <Form.Label>Moves</Form.Label>
                              <Form.Control
                                  as="textarea"
                                  rows={3}
                                  onChange={this.handleMoves}
                                  required={true}/>
                          </Form.Group>
                      </Modal.Body>
                      <Modal.Footer>
                          <Button variant={"secondary"} onClick={this.handleClose}>
                              Close
                          </Button>
                          <Button variant={"primary"} type={"submit"}>
                              Add
                          </Button>
                      </Modal.Footer>
                  </Form>
              </Modal>
          </>
        );
    }
}

class SearchRecord extends React.Component {
    resetStateQuery() {
        this.setState(prevState => ({
            ...prevState,
            query: {
                minDate: null,
                maxDate: null,
                nickOne: '',
                nickTwo: '',
                draw: 1,
                oneWin: 1,
                twoWin: 1
            }
        }))
    }

    constructor(props) {
        super(props);
        this.state = {
            query: {
                minDate: null,
                maxDate: null,
                nickOne: '',
                nickTwo: '',
                draw: 1,
                oneWin: 1,
                twoWin: 1
            },
            show: false
        }

        this.handleWinner = this.handleWinner.bind(this);
        this.handleShow = this.handleShow.bind(this);
        this.updateFromChildInterval = this.updateFromChildInterval.bind(this);
        this.updateFromChildSingleInput = this.updateFromChildSingleInput.bind(this);
        this.handleClose = this.handleClose.bind(this);
        this.handleSubmit = this.handleSubmit.bind(this);
        this.resetStateQuery = this.resetStateQuery.bind(this);
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
        this.setState(prevState => ({
            ...prevState,
            show: false
        }));
        this.resetStateQuery();
    }

    handleShow() {
        this.setState(prevState => ({
            ...prevState,
            show: true
        }));
        this.resetStateQuery();
    }

    handleWinner(field) {
        this.state.query[field] ^= 1;
    }

    async handleSubmit(e) {
        e.preventDefault();
        let query = getQueryPath(this.state.query);
        query = '&' + query.substring(1);
        this.props.runQuery(query);
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
                                type={"date"}
                                name={'Date'} />
                            <SingleInput
                                updateParent={this.updateFromChildSingleInput}
                                valueName={'nickOne'}
                                valueTitle={'Nickname One'}/>
                            <SingleInput
                                updateParent={this.updateFromChildSingleInput}
                                valueName={'nickTwo'}
                                valueTitle={'Nickname Two'}/>
                            <Row>
                                <Col>
                                    <Form.Check
                                        label={"1–0"}
                                        onClick={() => this.handleWinner('oneWin')}
                                        defaultChecked={true}/>
                                </Col>
                                <Col>
                                    <Form.Check
                                        label={"½–½"}
                                        onClick={() => this.handleWinner('draw')}
                                       defaultChecked={true}/>
                                </Col>
                                <Col>
                                    <Form.Check
                                        label={"0–1"}
                                        onClick={() => this.handleWinner('twoWin')}
                                        defaultChecked={true}/>
                                </Col>
                            </Row>
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
        );
    }
}

class RecordsTable extends React.Component {
    constructor(props) {
        super(props);
        this.handleSort = this.handleSort.bind(this);
    }

    handleSort() {
        this.props.changeSort();
    }

    getResult(winner) {
        return winner === 0 ? '½–½' : winner === 1 ? '1–0' : '0–1'
    }

    render() {
        const recordsTable = this.props.records.map(record =>
        <tr key={record.id}>
            <td onClick={() => this.props.changeMoves(record.moves,
                this.getResult(record.winner),
                record.nickOne,
                record.nickTwo,
                record.date)}>{record.date}</td>
            <td onClick={() => this.props.changeMoves(record.moves,
                this.getResult(record.winner),
                record.nickOne,
                record.nickTwo,
                record.date)}>{record.nickOne}</td>
            <td onClick={() => this.props.changeMoves(record.moves,
                this.getResult(record.winner),
                record.nickOne,
                record.nickTwo,
                record.date)}>{this.getResult(record.winner)}</td>
            <td onClick={() => this.props.changeMoves(record.moves,
                this.getResult(record.winner),
                record.nickOne,
                record.nickTwo,
                record.date)}>{record.nickTwo}</td>
        </tr>);
        return (
            <Table striped bordered hover>
                <thead>
                    <tr>
                        <th onClick={this.handleSort}>Date</th>
                        <th>Nick One</th>
                        <th>Result</th>
                        <th>Nick Two</th>
                    </tr>
                </thead>
                <tbody>
                    {recordsTable}
                </tbody>
            </Table>
        );
    }
}

class Records extends React.Component {
    constructor(props) {
        super(props);
        this.state = {
            gameId: 0,
            isCorrect: true,
            isLoaded: false,
            records: [],
            gameName: '',
            sortDirection: true,
            query: '',
            moves: {
                moves: '',
                result: '',
                nickOne: '',
                nickTwo: '',
                date: null
            }
        }
        this.updateRecords = this.updateRecords.bind(this);
        this.runQuery = this.runQuery.bind(this);
        this.changeSort = this.changeSort.bind(this);
        this.changeMoves = this.changeMoves.bind(this);
        this.addRecord = this.addRecord.bind(this);
    }

    async addRecord(newRecord) {
        newRecord.gameId = this.state.gameId;
        await fetch('/' + recordsURI + '/', POST(newRecord));
        await this.runQuery(this.state.query);
    }

    updateRecords(records) {
        this.setState(prevState => ({
            ...prevState,
            records: records
        }))
    }

    async runQuery(query) {
        this.setState(prevState => ({
            ...prevState,
            isLoaded: false
        }));
        const response = await fetch('/' + recordsURI + '/query' +
            '?game=' + this.state.gameId +
            '&sort=' + this.state.sortDirection +
            query, GET);
        this.setState(prevState => ({
            ...prevState,
            query: query
        }));
        this.updateRecords(await response.json());
        this.setState(prevState => ({
            ...prevState,
            isLoaded: true
        }));
    }

    changeMoves(moves, result, nickOne, nickTwo, date) {
        this.setState(prevState => ({
            ...prevState,
            moves: {
                moves: moves,
                result: result,
                nickOne: nickOne,
                nickTwo: nickTwo,
                date: date
            }
        }));
    }


    async getRecords() {
        const response = await fetch('/' + recordsURI +
                                    '?game=' + this.state.gameId +
                                    '&sort=' + this.state.sortDirection, GET);
        return await response.json();
    }

    async changeSort() {
        await this.setState(prevState => ({
            ...prevState,
            sortDirection: this.state.sortDirection ^ 1
        }));
        await this.runQuery(this.state.query);
    }

    async componentDidMount() {
        const match = checkPathId(window.location.pathname,
            'games/records/:id');
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

        const game = await fetchObject('games', match.id);
        this.setState(prevState => ({
            ...prevState,
            gameName: game.name
        }))
        let records = await this.getRecords();
        this.setState(prevState => ({
            ...prevState,
            records: records,
            isLoaded: true
        }))
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
                            <Container>
                                <Row>
                                    <Col>
                                        <h2>{this.state.gameName} games</h2>
                                    </Col>
                                    <Col md={"auto"}>
                                        <AddRecord addRecord={this.addRecord}/>
                                    </Col>
                                    <Col md={"auto"}>
                                        <SearchRecord runQuery={this.runQuery}/>
                                    </Col>
                                </Row>
                                <Row>
                                    <Col md={"auto"}>
                                        <Form.Group className="mb-3" controlId="exampleForm.ControlTextarea1">
                                            <Form.Label>{this.state.moves.nickOne} {this.state.moves.result} {this.state.moves.nickTwo} {this.state.moves.date}</Form.Label>
                                            <Form.Control as="textarea" rows={3} value={this.state.moves.moves} readOnly/>
                                        </Form.Group>
                                    </Col>
                                    <Col>
                                        <RecordsTable
                                            records={this.state.records}
                                            changeSort={this.changeSort}
                                            changeMoves={this.changeMoves}
                                            removeRecord={this.removeRecord}/>
                                    </Col>
                                </Row>
                            </Container>
                        </Stack> :
                        <Stack gap={2} className={"col-md-10 mx-auto"}>
                            <Row>
                                <Col align={"center"}>
                                    <Spinner animation={"border"}/>
                                </Col>
                            </Row>
                        </Stack>
                }
            </>
        );
    }
}

export {Records};
