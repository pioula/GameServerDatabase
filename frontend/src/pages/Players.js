import React from 'react';
import {Button, Col, Form, Modal, Row, Stack, Table} from "react-bootstrap";
import {fetchObject, fetchTable, GET, getQueryPath, postObject} from "../utils/fetch_utils";
import {Interval, SingleInput, updateFromInterval, updateFromSingleInput} from "../utils/class_utils";

const table = 'players';

class AddPlayer extends React.Component {
    emptyQuery = {
        nick: '',
        firstName: '',
        lastName: '',
        age: 0,
        password: ''
    }

    constructor(props) {
        super(props);
        this.state = {
            query: this.emptyQuery,
            show: false,
            validated: false
        }

        this.handleClose = this.handleClose.bind(this);
        this.handleShow = this.handleShow.bind(this);
        this.handleSubmit = this.handleSubmit.bind(this);
        this.updateFromChildSingleInput = this.updateFromChildSingleInput.bind(this);
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
            query: this.emptyQuery,
            show: false
        }));
    }

    handleShow() {
        this.setState(prevState => ({
            ...prevState,
            show: true,
            validated: false
        }))
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
            let player = await fetchObject('players', this.state.query.nick);
            if (player.age >= 0) {
                console.log("error!");
                this.handleClose();
                return;
            }
            const newPlayer = {
                ...this.emptyQuery,
                nick: this.state.query.nick,
                firstName: this.state.query.firstName,
                lastName: this.state.query.lastName,
                age: this.state.query.age,
                password: this.state.query.password
            }

            const players = await postObject(table, newPlayer);
            this.props.updatePlayers(players);
            this.handleClose();
        }
    }

    render() {
        return (
            <>
                <Button variant={"success"} onClick={this.handleShow}>
                    Add new player
                </Button>

                <Modal size={"lg"} show={this.state.show} onHide={this.handleClose}>
                    <Modal.Header closeButton>
                        <Modal.Title>Add new player</Modal.Title>
                    </Modal.Header>
                    <Form noValidate validated={this.state.validated} onSubmit={this.handleSubmit}>
                        <Modal.Body>
                            <SingleInput
                                updateParent={this.updateFromChildSingleInput}
                                valueName={'nick'}
                                valueTitle={'Nickname'}
                                required={true}/>
                            <SingleInput
                                updateParent={this.updateFromChildSingleInput}
                                valueName={'password'}
                                valueTitle={'Password'}
                                required={true}/>
                            <SingleInput
                                updateParent={this.updateFromChildSingleInput}
                                valueName={'firstName'}
                                valueTitle={'First Name'}
                                required={true}/>
                            <SingleInput
                                updateParent={this.updateFromChildSingleInput}
                                valueName={'lastName'}
                                valueTitle={'Last Name'}
                                required={true}/>
                            <SingleInput
                                updateParent={this.updateFromChildSingleInput}
                                valueName={'age'}
                                valueTitle={'Age'}
                                type={"number"}
                                required={true}/>
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

class SearchPlayer extends React.Component {
    emptyQuery = {
        nick: '',
        firstName: '',
        lastName: '',
        minAge: 0,
        maxAge: 0
    }

    constructor(props) {
        super(props);
        this.state = {
            show: false,
            query: this.emptyQuery
        }

        this.handleClose = this.handleClose.bind(this);
        this.handleShow = this.handleShow.bind(this);
        this.handleSubmit = this.handleSubmit.bind(this);
        this.updateFromChildSingleInput = this.updateFromChildSingleInput.bind(this);
        this.updateFromChildInterval = this.updateFromChildInterval.bind(this);
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
            ...this.emptyQuery,
            show: false
        });
    }

    handleShow() {
        this.setState(prevState => ({
            ...prevState,
            show: true
        }));
    }

    async handleSubmit(e) {
        e.preventDefault();

        const response = await fetch('/' + table + '/get-players-query' +
                                                    getQueryPath(this.state.query), GET);

        this.props.updatePlayers(await response.json());
        this.handleClose();
    }


    render() {
        return (
            <>
                <Button variant={"primary"} onClick={this.handleShow}>
                    Search players
                </Button>

                <Modal size={"lg"} show={this.state.show} onHide={this.handleClose}>
                    <Modal.Header closeButton>
                        <Modal.Title>Search</Modal.Title>
                    </Modal.Header>
                    <Form onSubmit={this.handleSubmit}>
                        <Modal.Body>
                            <SingleInput
                                updateParent={this.updateFromChildSingleInput}
                                valueName={'nick'}
                                valueTitle={'Nickname'}/>
                            <SingleInput
                                updateParent={this.updateFromChildSingleInput}
                                valueName={'firstName'}
                                valueTitle={'First Name'}/>
                            <SingleInput
                                updateParent={this.updateFromChildSingleInput}
                                valueName={'lastName'}
                                valueTitle={'Last Name'}/>
                            <Interval
                                updateParent={this.updateFromChildInterval}
                                name={'Age'}/>
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

class PlayersTable extends React.Component {
    render() {
        const playersTable = this.props.players.map(player =>
        <tr key={player.nick}>
            <td>{player.nick}</td>
            <td>{player.password}</td>
            <td>{player.firstName}</td>
            <td>{player.lastName}</td>
            <td>{player.age}</td>
        </tr>);
        return (
            <Table striped>
                <thead>
                    <tr>
                        <th>Nick</th>
                        <th>Password</th>
                        <th>First Name</th>
                        <th>Last Name</th>
                        <th>Age</th>
                    </tr>
                </thead>
                <tbody>
                    {playersTable}
                </tbody>
            </Table>
        );
    }
}

class Players extends React.Component {
    constructor(props) {
        super(props);
        this.state = {
            players: []
        };
        this.updatePlayers = this.updatePlayers.bind(this);
    }

    updatePlayers(players) {
        this.setState(prevState => ({
            ...prevState,
            players: players
        }));
    }

    async componentDidMount() {
        this.updatePlayers(await fetchTable(table));
    }

    render() {
        return (
            <>
                <Stack gap={2} className={"col-md-10 mx-auto"}>
                    <Row>
                        <Col>
                            <h2>Players</h2>
                        </Col>
                        <Col md={"auto"}>
                            <AddPlayer updatePlayers={this.updatePlayers}/>
                        </Col>
                        <Col md={"auto"}>
                            <SearchPlayer updatePlayers={this.updatePlayers}/>
                        </Col>
                    </Row>
                    <Row>
                        <Col>
                            <PlayersTable players={this.state.players} />
                        </Col>
                    </Row>
                </Stack>
            </>
        );
    }
}

export default Players;